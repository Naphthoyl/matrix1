#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iostream>

template <typename T>
class List;

template <typename T>
class Node;

template <typename T>
class Matrix {
private:
    int n;
    T** a;
    friend class List<T>;
    friend class Node<T>;

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

extern template class Matrix<int>;
extern template class Matrix<double>;

#endif
