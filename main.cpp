#include <iostream>
#include <fstream>

#include "matrix.h"
#include "list.h"

int main() {
    std::ifstream fin("text.txt");
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
