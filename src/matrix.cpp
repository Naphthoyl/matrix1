#include "matrix.h"

#include <iostream>

Matrix::Matrix() : n(0), a(nullptr) {
    std::cout << "in construck Maxrix" << std::endl;
}

Matrix::Matrix(int size) : n(size), a(nullptr) {
    try {
        a = new int*[n];
        for (int i = 0; i < n; i++) {
            a[i] = nullptr;
        }

        try {
            for (int i = 0; i < n; i++) {
                a[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    a[i][j] = 0;
                }
            }
        }
        catch (...) {
            for (int i = 0; i < n; i++) {
                delete[] a[i];
            }
            delete[] a;
            n = 0;
            a = nullptr;
            return;
        }
    }
    catch (...) {
        delete[] a;
        n = 0;
        a = nullptr;
        return;
    }
}

Matrix::~Matrix() {
    if (a != nullptr) {
        for (int i = 0; i < n; i++) {
            if (a[i]) {
                delete[] a[i];
            }
        }
        delete[] a;
    }
}

Matrix::Matrix(const Matrix& other) : n(other.n), a(nullptr) {
    if (other.a == nullptr || other.n == 0) {
        n = 0;
        a = nullptr;
        return;
    }

    try {
        a = new int*[n];
        for (int i = 0; i < n; i++) {
            a[i] = nullptr;
        }

        try {
            for (int i = 0; i < n; i++) {
                a[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    a[i][j] = other.a[i][j];
                }
            }
        }
        catch (...) {
            for (int i = 0; i < n; i++) {
                delete[] a[i];
            }
            delete[] a;
            n = 0;
            a = nullptr;
            return;
        }
    }
    catch (...) {
        delete[] a;
        n = 0;
        a = nullptr;
        return;
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    if (a != nullptr) {
        for (int i = 0; i < n; i++) {
            if (a[i]) {
                delete[] a[i];
            }
        }
        delete[] a;
    }

    n = other.n;
    a = nullptr;

    if (other.a == nullptr || other.n == 0) {
        n = 0;
        a = nullptr;
        return *this;
    }

    try {
        a = new int*[n];
        for (int i = 0; i < n; i++) {
            a[i] = nullptr;
        }

        try {
            for (int i = 0; i < n; i++) {
                a[i] = new int[n];
                for (int j = 0; j < n; j++) {
                    a[i][j] = other.a[i][j];
                }
            }
        }
        catch (...) {
            for (int i = 0; i < n; i++) {
                delete[] a[i];
            }
            delete[] a;
            n = 0;
            a = nullptr;
            return *this;
        }
    }
    catch (...) {
        delete[] a;
        n = 0;
        a = nullptr;
        return *this;
    }
    return *this;
}

void Matrix::input(std::ifstream& fin) {
    std::cout << "vvedite elementi" << std::endl;
    if (a == nullptr || n == 0) {
        std::cout << "Matrix is empty\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> a[i][j];
        }
    }
}

void Matrix::show() {
    if (a == nullptr || n == 0) {
        std::cout << "Matrix is empty\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << a[i][j] << "  ";
        }
        std::cout << "\n";
    }
}

Matrix Matrix::operator+(const Matrix& other) {
    if (a == nullptr || other.a == nullptr || n == 0 || n != other.n) {
        return Matrix();
    }

    Matrix result(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.a[i][j] = a[i][j] + other.a[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) {
    if (a == nullptr || other.a == nullptr || n == 0 || n != other.n) {
        return Matrix();
    }

    Matrix result(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * other.a[k][j];
            }
            result.a[i][j] = sum;
        }
    }
    return result;
}

void Matrix::sledMatrix() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + a[i][i];
    }
    std::cout << sum << std::endl;
}
