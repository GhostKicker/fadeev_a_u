#define _SCL_SECURE_NO_WARNINGS

#include <string>
#include <sstream>
#include <iostream>
#include <map> 
#include <vector>
#include <fstream>
#include <algorithm>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


#include "tiny_dnn/tiny_dnn.h"

typedef std::map<tiny_dnn::label_t, std::map<tiny_dnn::label_t, int>> conf_m;
typedef std::tuple<std::string, double, double, double, double> nn_datas;


using namespace std;
using namespace tiny_dnn;

const string sep = ";";


int number_of_dots                                                   = 0;
string root_path                                                     = "";
string path_to_models                                                = "";
string path_to_data                                                  = "";
string path_to_databases                                             = "";
int number_of_tested                                                 = 0;

tiny_dnn::core::backend_t backend_type                               = tiny_dnn::core::default_engine();

std::vector<tiny_dnn::label_t> test_labels;
std::vector<tiny_dnn::vec_t> test_images;
std::set<std::string> nns;

static void construct_net(tiny_dnn::network<tiny_dnn::sequential> &nn,
    tiny_dnn::core::backend_t backend_type);


string find_file_name(string& full_path)
{
    string res = "";
    ptrdiff_t index = full_path.size();
    --index;
    while (index >= 0 && full_path[index] != '\\')
    {
        res = full_path[index] + res;
        --index;
    }
    return res;
}


bool stream_is_empty(std::stringstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

bool istream_is_empty(std::istream& pFile)
{
    return pFile.peek() == std::istream::traits_type::eof();
}

double Precision_i(const conf_m& m, int i)
{
    int num = 0;
    if (m.find(i) != m.end() && m.at(i).find(i) != m.at(i).end()) num = m.at(i).at(i);
    int denum = 0;
    for (int j = 0; j <= 9; j++)
    {
        if (m.find(i) != m.end() && m.at(i).find(j) != m.at(i).end()) denum += m.at(i).at(j);
    }
    if (denum > 0) return (double)(num) / denum; else return 0;
}

double Recall_i(const conf_m& m, int i)
{
    int num = 0;
    if (m.find(i) != m.end() && m.at(i).find(i) != m.at(i).end()) num = m.at(i).at(i);
    int denum = 0;
    for (int j = 0; j <= 9; j++)
    {
        if (m.find(j) != m.end() && m.at(j).find(i) != m.at(j).end())   denum += m.at(j).at(i);
    }
    if (denum > 0) return (double)(num) / denum; else return 0;
}

double Precision(const conf_m& m)
{
    int denumm = 10;
    double totalPrecition = 0;
    for (int i = 0; i <= 9; i++)
    {
        double val = Precision_i(m, i);
        if (val == 0) denumm -= 1;
        totalPrecition += val;
    }
    return totalPrecition / denumm;
}

double Recall(const conf_m& m)
{
    int denumm = 10;
    double totalRecall = 0;
    for (int i = 0; i <= 9; i++)
    {
        double val = Recall_i(m, i);
        if (val == 0) denumm -= 1;
        totalRecall += val;
    }
    return totalRecall / denumm;
}

double F1_i(const conf_m& m, int i)
{
    return 2 * (Precision_i(m, i)*Recall_i(m, i)) / (Precision_i(m, i) + Recall_i(m, i));
}

double F1(const conf_m& m)
{
    return 2 * (Precision(m)*Recall(m)) / (Precision(m) + Recall(m));
}

void fill_massives()
{
    std::cout << "loading databases" << std::endl;

    std::cout << "Loading test labels" << std::endl;
    tiny_dnn::parse_mnist_labels(root_path + path_to_databases + "/t10k-labels.idx1-ubyte",
        &test_labels);
    std::cout << "Loading test images" << std::endl;
    tiny_dnn::parse_mnist_images(root_path + path_to_databases + "/t10k-images.idx3-ubyte",
        &test_images, -1.0, 1.0, 2, 2);

    std::cout << "loading done!" << std::endl;

}


static std::tuple<double, double, double, double> testing(
    tiny_dnn::network<tiny_dnn::sequential>& nn,
    tiny_dnn::core::backend_t backend_type,
    std::vector<tiny_dnn::label_t>& test_labels,
    std::vector<tiny_dnn::vec_t>& test_images,
    std::string net_name,
    std::ofstream& ofstr) {


    tiny_dnn::result res = nn.test(test_images, test_labels);

    double prec = Precision(res.confusion_matrix);
    double rec = Recall(res.confusion_matrix);
    double f1 = F1(res.confusion_matrix);
    double acc = (double)res.num_success / res.num_total;
    std::vector<std::vector<double>> dec_values;
    ofstr << 1000 * (double)res.num_success / res.num_total << sep << 1000 * prec << sep << 1000 * rec << sep << 1000 * f1 << endl;
    std::cout << res.num_success << "/" << res.num_total << "     " << prec << "       " << rec << "       " << f1 << std::endl;
    return std::make_tuple(acc, prec, rec, f1);
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

const enum cmds
{
    START,
    BEST,
    WORST
};

const std::map<std::string, int> cmdMap
{
    { "--start", START },
    { "--best", BEST },
    { "--worst", WORST }
};

void start(int argc, int i, char** argv);
void best(int argc, int i, char** argv);
void worst(int argc, int i, char** argv);

void Initialize() 
{
    cout << "Initialization..." << endl;
    string s = "";
    ifstream configfile("config.txt");
    cout << "reading from config..." << endl;
    getline(configfile, s);
    number_of_dots = stoi(s.substr(s.find('=') + 1));
    getline(configfile, s);
    root_path = s.substr(s.find('=') + 1);
    getline(configfile, s);
    path_to_models = (s.substr(s.find('=') + 1));
    getline(configfile, s);
    path_to_data = (s.substr(s.find('=') + 1));
    getline(configfile, s);
    path_to_databases = (s.substr(s.find('=') + 1));
    getline(configfile, s);
    number_of_tested = stoi(s.substr(s.find('=') + 1));
    cout << "----- starting with these parameters -----" << endl;
    cout << "number_of_dots = " << number_of_dots << endl;
    cout << "root_path = " << root_path << endl;
    cout << "path_to_models = " << path_to_models << endl;
    cout << "path_to_data = " << path_to_data << endl;
    cout << "path_to_databases = " << path_to_databases << endl;
    cout << "number_of_tested = " << number_of_tested << endl;
    cout << "------------------------------------------" << endl;
}

int main(int argc, char** argv)
{
    Initialize();
    for (int i = 1; i < argc; i++)
    {
        string command = "";
        command = argv[i];
        if (cmdMap.find(command) != cmdMap.end())
        {
            cout << "--------------------" << endl;
            switch (cmdMap.at(command))
            {
            case START: cout << "invoking 'start' command" << endl; start(argc, i, argv); break;
            case BEST: cout << "invoking 'best' command" << endl; best(argc, i, argv); break;
            case WORST: cout << "invoking 'worst-tests' command" << endl; worst(argc, i, argv); break;
            }
        }
    }
}

void start(int argc, int i, char** argv)
{
    set<string> nns;
    i++;
    string cur = "";
    while (!(cur[0] == '-' && cur[1] == '-') && i < argc)
    {
        cur = argv[i];
        try {
            std::ifstream ifs((root_path + path_to_models + cur).c_str(), std::ios::binary | std::ios::in);
            if ((ifs.fail() || ifs.bad()) && cur != "all") throw (nn_error("err"));
            if (cur != "all") nns.insert(cur);
            if (cur == "all") cout << "going to use all models from root_directory/models_directory" << endl;
        }
        catch (nn_error qwe) {
            cout << "net with name " << cur << " is not found" << endl;
        }
        i++;
        if (i < argc) cur = argv[i];
    }
    if (cur == "all")
    {
        for (auto& p : fs::directory_iterator(root_path + path_to_models))
        {
           // cout << p << endl;
            stringstream tmpstr(ios::in | ios::out);
            tmpstr << p;
            string namecur;
            while (!stream_is_empty(tmpstr))
            {
                string s;
                tmpstr >> s;
                namecur += s;
            }
            namecur = find_file_name(namecur);
            nns.insert(namecur);
        }

    }

    if (nns.begin() != nns.end() && test_images.size() == 0) fill_massives();


    try {
        std::cout << "start testing" << std::endl;
        if (nns.begin() == nns.end()) std::cout << "no nets are opened" << std::endl;
        std::ofstream general_i;
        general_i << "name" + sep + "accuracy" + sep + "precision" + sep + "recall" + sep + "f1" << endl;
        if (nns.begin() != nns.end()) general_i = std::ofstream((root_path + path_to_data + "general_info.csv").c_str());
        for (std::set<std::string>::iterator curnet = nns.begin(); curnet != nns.end(); curnet++)
        {
            tiny_dnn::network<tiny_dnn::sequential> cur_nn;

            construct_net(cur_nn, backend_type);
            cur_nn.load(path_to_models + (*curnet));
            std::cout << "currently testing " + (*curnet) << std::endl;

            std::ofstream ofs((path_to_data + (*curnet) + ".csv").c_str());
            ofs << "accuracy;precision;recall;f1" << endl;
            double macro_av_acc = 0;
            double macro_av_prec = 0;
            double macro_av_rec = 0;
            double macro_av_f1 = 0;
            for (int i = 0; i < number_of_dots; i++)
            {

                std::vector<tiny_dnn::label_t> test_labels_r;
                std::vector<tiny_dnn::vec_t> test_images_r;
                for (int cur = 0; cur < number_of_tested; cur++)
                {
                    int randcur = rand() % test_images.size();
                    test_labels_r.push_back(test_labels[randcur]);
                    test_images_r.push_back(test_images[randcur]);
                }


                try {
                    auto res = testing(cur_nn, backend_type, test_labels_r, test_images_r, (*curnet), ofs);
                    macro_av_acc += get<0>(res);
                    macro_av_prec += get<1>(res);
                    macro_av_rec += get<2>(res);
                    macro_av_f1 += get<3>(res);
                    
                }
                catch (tiny_dnn::nn_error &err) {
                    std::cerr << "Exception: " << err.what() << std::endl;
                }
            }
            macro_av_acc /= number_of_dots;
            macro_av_prec /= number_of_dots;
            macro_av_rec /= number_of_dots;
            macro_av_f1 /= number_of_dots;

            general_i << (*curnet) << sep
                << macro_av_acc << sep
                << macro_av_prec << sep
                << macro_av_rec << sep
                << macro_av_f1 << endl;
            ofs.close();
        }
        general_i.close();
        std::cout << "stop testing" << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "some error has occured" << std::endl;
    }
    catch (tiny_dnn::nn_error& er) {
        std::cout << "some error has occured" << std::endl;
    }
}


void best(int argc, int i, char** argv)
{
    i++;
    string cur = "";
    if (i < argc)
    {
        cur = argv[i];
    }
    else return;

    ptrdiff_t num = 0;

    try
    {
        num = stoi(cur);
    }
    catch (std::exception e) {
        return;
    }

    vector<nn_datas> nns;
    string data_cur;
    ifstream general_i_stream(root_path + path_to_data + "general_info.csv");
    while (!istream_is_empty(general_i_stream))
    {
        getline(general_i_stream, data_cur);
        string name = data_cur.substr(0, data_cur.find(sep));
        data_cur = data_cur.substr(data_cur.find(sep) + 1);
        double acc = stod(data_cur.substr(0, data_cur.find(sep)));
        data_cur = data_cur.substr(data_cur.find(sep) + 1);
        double prec = stod(data_cur.substr(0, data_cur.find(sep)));
        data_cur = data_cur.substr(data_cur.find(sep) + 1);
        double rec = stod(data_cur.substr(0, data_cur.find(sep)));
        data_cur = data_cur.substr(data_cur.find(sep) + 1);
        double f1 = stod(data_cur.substr(0, data_cur.find(sep)));

        nns.push_back(make_tuple(name, acc, prec, rec, f1));
    }

    num = min(static_cast<ptrdiff_t>(nns.size()), num);

    std::ofstream beststr;
    if (nns.begin() != nns.end()) beststr = std::ofstream((root_path + path_to_data + "best.txt").c_str());
    cout << "output of best " << num << " models" << endl;
    cout << "best by accuracy" << endl;
    beststr << "output of best " << num << " models" << endl;
    beststr << "best by accuracy" << endl;

    sort(nns.begin(), nns.end(),
        [](nn_datas& lhs, nn_datas& rhs) -> bool
    {
        return get<1>(lhs) > get<1>(rhs);
    });

    for (ptrdiff_t i = 0; i < num; ++i)
    {
        cout << i + 1 << "     " << get<0>(nns[i]) << "    " << get<1>(nns[i]) << endl;
        beststr << i + 1 << "     " << get<0>(nns[i]) << "    " << get<1>(nns[i]) << endl;
    }

    cout << "best by precision" << endl;
    beststr << "best by precision" << endl;
    sort(nns.begin(), nns.end(),
        [](nn_datas& lhs, nn_datas& rhs) -> bool
    {
        return get<2>(lhs) > get<2>(rhs);
    });
    for (ptrdiff_t i = 0; i < num; ++i)
    {
        cout << i + 1 << "     " << get<0>(nns[i]) << "    " << get<2>(nns[i]) << endl;
        beststr << i + 1 << "     " << get<0>(nns[i]) << "    " << get<2>(nns[i]) << endl;
    }

    cout << "best by recall" << endl;
    beststr << "best by recall" << endl;
    sort(nns.begin(), nns.end(),
        [](nn_datas& lhs, nn_datas& rhs) -> bool
    {
        return get<3>(lhs) > get<3>(rhs);
    });
    for (ptrdiff_t i = 0; i < num; ++i)
    {
        cout << i + 1 << "     " << get<0>(nns[i]) << "    " << get<3>(nns[i]) << endl;
        beststr << i + 1 << "     " << get<0>(nns[i]) << "    " << get<3>(nns[i]) << endl;
    }

    cout << "best by f1" << endl;
    beststr << "best by f1" << endl;
    sort(nns.begin(), nns.end(),
        [](nn_datas& lhs, nn_datas& rhs) -> bool
    {
        return get<4>(lhs) > get<4>(rhs);
    });
    for (ptrdiff_t i = 0; i < num; ++i)
    {
        cout << i + 1 << "     " << get<0>(nns[i]) << "    " << get<4>(nns[i]) << endl;
        beststr << i + 1 << "     " << get<0>(nns[i]) << "    " << get<4>(nns[i]) << endl;
    }
    beststr.close();
}

void worst(int argc, int i, char** argv)
{
    i++;
    string cur = "";
    if (i < argc)
    {
        cur = argv[i];
    }
    else return;

    ptrdiff_t num = 0;

    try
    {
        num = stoi(cur);
    }
    catch (std::exception e) {
        return;
    }
    if (test_labels.size() == 0) fill_massives();
    set<string> nns;
    vector<int> right = (vector<int>(test_labels.size(), 0));

    for (auto& p : fs::directory_iterator(root_path + path_to_models))
    {
        // cout << p << endl;
        stringstream tmpstr(ios::in | ios::out);
        tmpstr << p;
        string namecur;
        while (!stream_is_empty(tmpstr))
        {
            string s;
            tmpstr >> s;
            namecur += s;
        }
        namecur = find_file_name(namecur);
        nns.insert(namecur);
    }
    num = min(static_cast<ptrdiff_t>(right.size()), num);

    for (auto curnet = nns.cbegin(); curnet != nns.cend(); curnet++)
    {
        tiny_dnn::network<tiny_dnn::sequential> cur_nn;
        construct_net(cur_nn, backend_type);
        cur_nn.load(path_to_models + (*curnet));

        cout << "currently testing " << *curnet << endl;
        const ptrdiff_t mass_size = test_labels.size();
        for (ptrdiff_t i = 0; i < mass_size; ++i)
        {
            auto vec_l = vector<label_t>(1, test_labels[i]);
            auto vec_i = vector<vec_t>(1, test_images[i]);
            tiny_dnn::result res = cur_nn.test(vec_i, vec_l);
            right[i] += res.num_success;
            if ((i + 1) % 1000 == 0) cout << i + 1 << " tests done!" << endl;
        }
    }
    vector<pair<int, int>> worst;

    for (ptrdiff_t i = 0; i < right.size(); i++)
    {
        worst.push_back(make_pair(i + 1, right[i]));
    }

    sort(worst.begin(), worst.end(), 
        [](pair<int, int>& a, pair<int, int>& b) 
    {
        return a.second < b.second;
    });

    std::ofstream worststr((root_path + path_to_data + "worst-tests.txt").c_str());
    int nnsnum = nns.size();
    cout << "worst tests" << endl;
    worststr << "worst tests" << endl;
    for (ptrdiff_t i = 0; i < num; i++)
    {
        cout << worst[i].first << " - " << static_cast<double>(worst[i].second) / nnsnum << "%" << endl;
        worststr << worst[i].first << " - " << static_cast<double>(worst[i].second) / nnsnum << "%" << endl;
    }
}