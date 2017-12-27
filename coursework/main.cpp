#define _SCL_SECURE_NO_WARNINGS


#include <string>
#include <sstream>
#include <iostream>
#include <map> 
#include <vector>
#include <fstream>
#include <algorithm>

#include "tiny_dnn/tiny_dnn.h"

typedef std::map<tiny_dnn::label_t, std::map<tiny_dnn::label_t, int>> conf_m;

int number_of_randoms_tests = 20;
int number_of_randoms_train = 20;
int number_of_iterations = 15;
double learning_rate = 1;
int epochs = 1;
std::string data_path = "C://tiny-dnn-master";
int minibatch_size = 1;
tiny_dnn::core::backend_t backend_type = tiny_dnn::core::default_engine();


std::vector<tiny_dnn::label_t> train_labels, test_labels;
std::vector<tiny_dnn::vec_t> train_images, test_images;

std::set<std::string> nns;

void Initialize();

//COMMANDS
void cmdHelp();
void open();
void opened();
void create();
void close();
void start();
void best();
void show();

void waitForCommands();


double Precition(const conf_m& m)
{
    double totalPrecition = 0;
    for (int i = 0; i < 9; i++)
    {
        int num = 0;
        if (m.find(i)!= m.end() && m.at(i).find(i) != m.at(i).end()) num = m.at(i).at(i);
        int denum = 0;
        for (int j = 0; j < 9; j++)
        {
            if (m.find(i) != m.end() && m.at(i).find(j) != m.at(i).end()) denum += m.at(i).at(j);
        }
        if (denum > 0) totalPrecition += (double)(num) / denum;
        totalPrecition;
    }
    return totalPrecition / 10;
}

double Recall(const conf_m& m)
{
    double totalRecall = 0;
    for (int i = 0; i < 9; i++)
    {
        int num = 0;
        if (m.find(i) != m.end() && m.at(i).find(i) != m.at(i).end()) num = m.at(i).at(i);
        int denum = 0;
        for (int j = 0; j < 9; j++)
        {
            if (m.find(j) != m.end() && m.at(j).find(i) != m.at(j).end())   denum += m.at(j).at(i);
        }
        if (denum > 0) totalRecall += (double)(num) / denum;
        totalRecall;
    }
    return totalRecall / 10;
}

int main() {
    Initialize();
    std::cout << "input '-help' for commands list" << std::endl;


    while (1) {
        std::cout << "----------------------" << std::endl;
        waitForCommands();
    }
    return 0;
}

const enum cmds
{
    HELP,//
    CREATE,//
    OPEN,//
    CLOSE,
    START,
    SHOW,
    BEST,
    OPENED,//
};

const std::map<std::string, int> cmdMap
{
    { "-help", HELP },
    { "-create", CREATE },
    { "-open", OPEN },
    { "-close", CLOSE },
    { "-start", START },
    { "-show", SHOW },
    { "-best", BEST },
    { "-opened", OPENED },
};

static void construct_net(tiny_dnn::network<tiny_dnn::sequential> &nn,
    tiny_dnn::core::backend_t backend_type) {
    // connection table [Y.Lecun, 1998 Table.1]
#define O true
#define X false
    // clang-format off
    static const bool tbl[] = {
        O, X, X, X, O, O, O, X, X, O, O, O, O, X, O, O,
        O, O, X, X, X, O, O, O, X, X, O, O, O, O, X, O,
        O, O, O, X, X, X, O, O, O, X, X, O, X, O, O, O,
        X, O, O, O, X, X, O, O, O, O, X, X, O, X, O, O,
        X, X, O, O, O, X, X, O, O, O, O, X, O, O, X, O,
        X, X, X, O, O, O, X, X, O, O, O, O, X, O, O, O
    };
    // clang-format on
#undef O
#undef X

    // construct nets
    //
    // C : convolution
    // S : sub-sampling
    // F : fully connected
    // clang-format off
    using fc = tiny_dnn::layers::fc;
    using conv = tiny_dnn::layers::conv;
    using ave_pool = tiny_dnn::layers::ave_pool;
    using tanh = tiny_dnn::activation::tanh;

    using tiny_dnn::core::connection_table;
    using padding = tiny_dnn::padding;

    nn << conv(32, 32, 5, 1, 6,   // C1, 1@32x32-in, 6@28x28-out
        padding::valid, true, 1, 1, backend_type)
        << tanh()
        << ave_pool(28, 28, 6, 2)   // S2, 6@28x28-in, 6@14x14-out
        << tanh()
        << conv(14, 14, 5, 6, 16,   // C3, 6@14x14-in, 16@10x10-out
            connection_table(tbl, 6, 16),
            padding::valid, true, 1, 1, backend_type)
        << tanh()
        << ave_pool(10, 10, 16, 2)  // S4, 16@10x10-in, 16@5x5-out
        << tanh()
        << conv(5, 5, 5, 16, 120,   // C5, 16@5x5-in, 120@1x1-out
            padding::valid, true, 1, 1, backend_type)
        << tanh()
        << fc(120, 10, true, backend_type)  // F6, 120-in, 10-out
        << tanh();
}

static void train_net(
    double learning_rate,
    const int n_train_epochs,
    const int n_minibatch,
    tiny_dnn::core::backend_t backend_type,
    std::vector<tiny_dnn::label_t>& train_labels,
    std::vector<tiny_dnn::vec_t>& train_images,
    std::vector<tiny_dnn::label_t>& test_labels,
    std::vector<tiny_dnn::vec_t>& test_images,
    std::string net_name,
    std::ofstream& ofstr) {
    tiny_dnn::network<tiny_dnn::sequential> nn;
    tiny_dnn::adagrad optimizer;

    construct_net(nn, backend_type);
    nn.load(net_name);

    optimizer.alpha *=
        std::min(tiny_dnn::float_t(4),
            static_cast<tiny_dnn::float_t>(sqrt(n_minibatch) * learning_rate));

    int epoch = 1;
    auto on_enumerate_epoch = [&]() {
        ++epoch;
        tiny_dnn::result res = nn.test(test_images, test_labels);
        std::cout << res.num_success << "/" << res.num_total << std::endl;

    };

    auto on_enumerate_minibatch = [&]() {};

    // training
    nn.train<tiny_dnn::mse>(optimizer, train_images, train_labels, n_minibatch,
        n_train_epochs, on_enumerate_minibatch,
        on_enumerate_epoch);


    tiny_dnn::result res = nn.test(test_images, test_labels);
    //res.print_detail(std::cout);

    nn.save(net_name);
    double prec = Precition(res.confusion_matrix);
    double rec = Recall(res.confusion_matrix);
    ofstr << prec << " " << rec << std::endl;
}


void waitForCommands()
{
    std::string command = "";
    std::cin >> command;
    if (cmdMap.find(command) != cmdMap.end())
    {
        switch (cmdMap.at(command)) {
        case HELP: cmdHelp(); break;
        case CREATE: create(); break;
        case OPEN: open(); break;
        case OPENED: opened(); break;
        case CLOSE: close(); break;
        case START: start(); break;
        case SHOW: show(); break;
        case BEST: best(); break;
        }
    }
    else {
        std::cout << "command not found. try -help for list" << std::endl;
    }
}

void cmdHelp()
{
    std::cout <<
        "---list of commands---" << std::endl <<
        "-create" << std::endl <<
        "-open" << std::endl <<
        "-close" << std::endl <<
        "-start" << std::endl <<
        "-show" << std::endl <<
        "-opened_list" << std::endl <<
        "-best" << std::endl;
}

void open()
{
    std::cout << "print name of net: ";
    std::string net_name = "";
    std::cin >> net_name;

    bool fine = false;

    try {
        std::ifstream ifs(net_name.c_str(), std::ios::binary | std::ios::in);
        if (ifs.fail() || ifs.bad()) throw tiny_dnn::nn_error("failed to open:" + net_name);
        fine = true;
    }
    catch (tiny_dnn::nn_error exc) {
        std::cout << "failed to load nn with name " << net_name << std::endl;
    }

    if (!fine) return;

    std::cout << "opened " << net_name << " successfully" << std::endl;
    nns.insert(net_name);
}

void opened()
{
    std::cout << "list of opened nns" << std::endl;
    for (std::set<std::string>::iterator it = nns.begin(); it != nns.end(); it++)
    {
        std::cout << (*it) << std::endl;
    }
    if (nns.begin() == nns.end()) std::cout << "List is empty! Nothing is opened!" << std::endl;
}

void create() {
    std::cout << "print name of new net: ";
    std::string net_name = "";
    std::cin >> net_name;

    bool fine = false;

    try {
        std::ifstream ifs(net_name.c_str(), std::ios::binary | std::ios::in);
        if (ifs.fail() || ifs.bad()) throw tiny_dnn::nn_error("failed to open:" + net_name);
        fine = true;
    }
    catch (tiny_dnn::nn_error exc) {

        tiny_dnn::network<tiny_dnn::sequential> nn;
        construct_net(nn, backend_type);
        nn.save(net_name);
        std::ofstream((net_name + "_t.txt").c_str());
        std::cout << "net with name " + net_name + " created successfully!" << std::endl;

    }
    if (fine)
    {
        std::cout << "net with name " + net_name + " already exists" << std::endl << "create new instead of already existing? (y/n)" << std::endl;
        std::string ans = "";
        std::cin >> ans;
        if (ans == "y" || ans == "Y")
        {
            tiny_dnn::network<tiny_dnn::sequential> nn;
            nn.save(net_name);
            std::cout << net_name + " has been overwritten" << std::endl; 

            std::ofstream ofs;
            ofs.open((net_name + "_t.txt").c_str(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();
        }
        else {
            std::cout << "nothing changed" << std::endl;
        }
    }

}

void close() {
    std::cout << "print name of new to close: ";
    std::string net_name = "";
    std::cin >> net_name;
    if (nns.find(net_name) != nns.end()) nns.erase(net_name);
    else std::cout << "there's no opened net with that name" << std::endl;
}

void start()
{
    try {
        std::cout << "start testing" << std::endl;
        if (nns.begin() == nns.end()) std::cout << "no nets are opened" << std::endl;
        for (std::set<std::string>::iterator curnet = nns.begin(); curnet != nns.end(); curnet++)
        {
            std::cout << "currently testing " + (*curnet) << std::endl;

            std::ofstream ofs(((*curnet) + "_t.txt").c_str());

            for (int i = 0; i < number_of_iterations; i++)
            {

                std::vector<tiny_dnn::label_t> test_labels_r, train_labels_r;
                std::vector<tiny_dnn::vec_t> test_images_r, train_images_r;
                for (int cur = 0; cur < number_of_randoms_train; cur++)
                {
                    int randcur = rand() % train_images.size();
                    train_labels_r.push_back(train_labels[randcur]);
                    train_images_r.push_back(train_images[randcur]);
                }
                for (int cur = 0; cur < number_of_randoms_tests; cur++)
                {
                    int randcur = rand() % test_images.size();
                    test_labels_r.push_back(test_labels[randcur]);
                    test_images_r.push_back(test_images[randcur]);
                }


                try {
                    train_net(learning_rate, epochs, minibatch_size, backend_type, train_labels_r, train_images_r, test_labels_r, test_images_r, (*curnet), ofs);
                }
                catch (tiny_dnn::nn_error &err) {
                    std::cerr << "Exception: " << err.what() << std::endl;
                }
            }
            ofs.close();
        }
        std::cout << "stop testing" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "some error has occured" << std::endl;
    }
    catch (tiny_dnn::nn_error& er) {
        std::cout << "some error has occured" << std::endl;
    }
}

void best()
{

}

void show()
{
    for (auto it = nns.begin(); it != nns.end(); it++)
    {

    }
}

void Initialize()
{
    std::cout << "Initialization started" << std::endl;

    std::cout << "Loading train labels" << std::endl;
    tiny_dnn::parse_mnist_labels(data_path + "/train-labels.idx1-ubyte",
        &train_labels);
    std::cout << "Loading train images" << std::endl;
    tiny_dnn::parse_mnist_images(data_path + "/train-images.idx3-ubyte",
        &train_images, -1.0, 1.0, 2, 2);
    std::cout << "Loading test labels" << std::endl;
    tiny_dnn::parse_mnist_labels(data_path + "/t10k-labels.idx1-ubyte",
        &test_labels);
    std::cout << "Loading test images" << std::endl;
    tiny_dnn::parse_mnist_images(data_path + "/t10k-images.idx3-ubyte",
        &test_images, -1.0, 1.0, 2, 2);

    std::cout << "Initialization ended. Enjoy!" << std::endl;

}