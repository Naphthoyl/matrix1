#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iostream>
#include <memory>

template <typename T>
class List;

template <typename T>
class Node;

template <typename T>
class Matrix {
private:
    int n;
   std::unique_ptr<std::unique_ptr<T[]>[]>a;
    friend class List<T>;
    friend class Node<T>;

public:
    Matrix();
    Matrix(int size);
    ~Matrix() = default;
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
