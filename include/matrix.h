#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>

class Matrix {
private:
    int n;
    int** a;
    friend class List;
    friend class Node;

public:
    Matrix();
    Matrix(int size);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    void input(std::ifstream& fin);
    void show();
    Matrix operator+(const Matrix& other);
    Matrix operator*(const Matrix& other);
    void sledMatrix();
};

#endif
