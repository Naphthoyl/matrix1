#include <iostream>
#include <fstream>
#include <string>

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

    std::ifstream fin(vm["file"].as<std::string>());
    if (!fin.is_open()) {
        std::cout << "error" << std::endl;
        return -1;
    }

    int n = 0; // кол-во матриц
    fin >> n;

    if (n <= 0) {
        std::cout << "error" << std::endl;
        return -2;
    }

    List ob1;

    int n1 = 0;
    for (int k = 0; k < n; k++) {
        fin >> n1;
        Matrix a(n1);
        a.input(fin);
        ob1.ins_before(a);
    }

    ob1.sled();
    ob1.show();

    return 0;
}
