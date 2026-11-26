#include <iostream>
#include <fstream>
#include <string>
#include <regex>


#include <boost/program_options.hpp>

#include "matrix.h"
#include "list.h"

namespace opt = boost::program_options;

int main(int argc, char** argv) {
    opt::options_description desc("All options");
    desc.add_options()
        ("file,f", opt::value<std::string>()->default_value("text.txt"), "input file with matrices")
        ("help", "produce help message")
    ;
    opt::variables_map vm;
    try {
        opt::store(opt::parse_command_line(argc, argv, desc), vm);
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }
        try {
            opt::store(opt::parse_config_file("config.cfg", desc), vm);
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        opt::notify(vm);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -3;
    }

    std::string file_name = vm["file"].as<std::string>();

    std::regex re_file(R"([\w./\\:-]+\.txt)", std::regex::icase);
    if (!std::regex_match(file_name, re_file)) {
        std::cout << "error: bad file name" << std::endl;
        return -4;
    }

    std::ifstream fin(file_name);
    if (!fin.is_open()) {
        std::cout << "error" << std::endl;
        return -1;
    }


    std::regex re_num(R"([1-9]\d{0,2}\r?)");   // целое от 1 до 999
    std::string line;
    int line_no = 0;

    std::getline(fin, line);
    line_no++;
    if (!std::regex_match(line, re_num)) {
        std::cout << "error in line " << line_no << ": bad number of matrices" << std::endl;
        return -5;
    }
    int count = std::stoi(line);

    for (int k = 0; k < count; k++) {
        std::getline(fin, line);
        line_no++;
        if (!std::regex_match(line, re_num)) {
            std::cout << "error in line " << line_no << ": bad matrix size" << std::endl;
            return -5;
        }
        int size = std::stoi(line);

        std::regex re_row("-?\\d{1,9}( -?\\d{1,9}){" + std::to_string(size - 1) + "}\\r?");
        for (int i = 0; i < size; i++) {
            std::getline(fin, line);
            line_no++;
            if (!std::regex_match(line, re_row)) {
                std::cout << "error in line " << line_no << ": bad matrix row" << std::endl;
                return -5;
            }
        }
    }
    fin.clear();
    fin.seekg(0);

    int n = 0; // кол-во матриц
    fin >> n;

    if (n <= 0) {
        std::cout << "error" << std::endl;
        return -2;
    }

    List<int> ob1;

    int n1 = 0;
    for (int k = 0; k < n; k++) {
        fin >> n1;
        Matrix<int> a(n1);
        a.input(fin);
        ob1.ins_before(a);
    }

    ob1.sled();
    ob1.show();

    return 0;
}
