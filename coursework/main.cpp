#define _SCL_SECURE_NO_WARNINGS
#include <string>
#include <sstream>
#include <iostream>
#include <map> 
#include <vector>
#include <fstream>

#include "tiny_dnn/tiny_dnn.h"

std::istringstream stre;

int number_of_randoms                       = 100;
int number_of_iterations                    = 10;
double learning_rate                        = 1;
int epochs                                  = 1;
std::string data_path                       = "C://tiny-dnn-master";
int minibatch_size                          = 16;
tiny_dnn::core::backend_t backend_type      = tiny_dnn::core::default_engine();


std::vector<tiny_dnn::label_t> train_labels;
std::vector<tiny_dnn::vec_t> train_images;

std::set<std::string> nns;

//COMMANDS
void cmdHelp();
void open();
void opened();
void create();
void close();
void start();
void best();
void show();
void quit();

void waitForCommands();


int main() {

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
    QUIT
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
    { "-quit", QUIT}
};

static void train(const std::string &data_dir_path,
    double learning_rate,
    const int n_train_epochs,
    const int n_minibatch,
    tiny_dnn::core::backend_t backend_type) {
    // specify loss-function and learning strategy
    tiny_dnn::network<tiny_dnn::sequential> nn;
    tiny_dnn::adagrad optimizer;

    construct_net(nn, backend_type);

    std::cout << "load models..." << std::endl;

    // load MNIST dataset
    std::vector<tiny_dnn::label_t> train_labels, test_labels;
    std::vector<tiny_dnn::vec_t> train_images, test_images;

    tiny_dnn::parse_mnist_labels(data_dir_path + "/train-labels.idx1-ubyte",
        &train_labels);
    tiny_dnn::parse_mnist_images(data_dir_path + "/train-images.idx3-ubyte",
        &train_images, -1.0, 1.0, 2, 2);
    tiny_dnn::parse_mnist_labels(data_dir_path + "/t10k-labels.idx1-ubyte",
        &test_labels);
    tiny_dnn::parse_mnist_images(data_dir_path + "/t10k-images.idx3-ubyte",
        &test_images, -1.0, 1.0, 2, 2);

    std::cout << "start training" << std::endl;

    tiny_dnn::progress_display disp(train_images.size());
    tiny_dnn::timer t;

    optimizer.alpha *=
        std::min(tiny_dnn::float_t(4),
            static_cast<tiny_dnn::float_t>(sqrt(n_minibatch) * learning_rate));

    int epoch = 1;
    // create callback
    auto on_enumerate_epoch = [&]() {
        std::cout << "Epoch " << epoch << "/" << n_train_epochs << " finished. "
            << t.elapsed() << "s elapsed." << std::endl;
        ++epoch;
        tiny_dnn::result res = nn.test(test_images, test_labels);
        std::cout << res.num_success << "/" << res.num_total << std::endl;

        disp.restart(train_images.size());
        t.restart();
    };

    auto on_enumerate_minibatch = [&]() { disp += n_minibatch; };

    // training
    nn.train<tiny_dnn::mse>(optimizer, train_images, train_labels, n_minibatch,
        n_train_epochs, on_enumerate_minibatch,
        on_enumerate_epoch);

    std::cout << "end training." << std::endl;

    // test and show results
    nn.test(test_images, test_labels).print_detail(std::cout);
    // save network model & trained weights
    nn.save("LeNet-model");
}

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
        case QUIT: quit(); break;
        }
    }
    else {
        std::cout << "connamd not found. try -help for list" << std::endl;
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
        nn.save(net_name);
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
            std::cout << net_name + " has been overwritten";
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
    if (train_labels.size() == 0 || train_images.size() == 0) 
    {
        tiny_dnn::parse_mnist_labels(data_path + "/train-labels.idx1-ubyte",
            &train_labels);
        tiny_dnn::parse_mnist_images(data_path + "/train-images.idx3-ubyte",
            &train_images, -1.0, 1.0, 2, 2);
    }
    for (std::set<std::string>::iterator curnet = nns.begin(); curnet != nns.end(); curnet++)
    {
        tiny_dnn::network<tiny_dnn::sequential> nn;
        nn.load(*curnet);

        for (int iter = 0; iter < number_of_iterations; iter++)
        {
            std::vector<tiny_dnn::label_t> tested_labels;
            std::vector<tiny_dnn::vec_t> tested_images;
            for (int cur = 0; cur < number_of_randoms; cur++)
            {
                int randcur = rand() % train_images.size();
                tested_labels.push_back(train_labels[randcur]);
                tested_images.push_back(train_images[randcur]);
            }
        }
    }
}
void best()
{

}
void show()
{

}
void quit() 
{

}