#include "matrix.h"

#include <iostream>

template <typename T>
Matrix<T>::Matrix() : n(0), a(nullptr) {
    std::cout << "in construck Maxrix" << std::endl;
}

template <typename T>
Matrix<T>::Matrix(int size) : n(size), a(nullptr) {
    try {
        a = new T*[n];
        for (int i = 0; i < n; i++) {
            a[i] = nullptr;
        }

        try {
            for (int i = 0; i < n; i++) {
                a[i] = new T[n];
                for (int j = 0; j < n; j++) {
                    a[i][j] = T();
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

template <typename T>
Matrix<T>::~Matrix() {
    if (a != nullptr) {
        for (int i = 0; i < n; i++) {
            if (a[i]) {
                delete[] a[i];
            }
        }
        delete[] a;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : n(other.n), a(nullptr) {
    if (other.a == nullptr || other.n == 0) {
        n = 0;
        a = nullptr;
        return;
    }

    try {
        a = new T*[n];
        for (int i = 0; i < n; i++) {
            a[i] = nullptr;
        }

        try {
            for (int i = 0; i < n; i++) {
                a[i] = new T[n];
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

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
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
        a = new T*[n];
        for (int i = 0; i < n; i++) {
            a[i] = nullptr;
        }

        try {
            for (int i = 0; i < n; i++) {
                a[i] = new T[n];
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

template <typename T>
void Matrix<T>::input(std::ifstream& fin) {
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

template <typename T>
void Matrix<T>::show() {
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

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
    if (a == nullptr || other.a == nullptr || n == 0 || n != other.n) {
        return Matrix<T>();
    }

    Matrix<T> result(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result.a[i][j] = a[i][j] + other.a[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
    if (a == nullptr || other.a == nullptr || n == 0 || n != other.n) {
        return Matrix<T>();
    }

    Matrix<T> result(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            T sum = T();
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * other.a[k][j];
            }
            result.a[i][j] = sum;
        }
    }
    return result;
}

template <typename T>
void Matrix<T>::sledMatrix() {
    T sum = T();
    for (int i = 0; i < n; i++) {
        sum = sum + a[i][i];
    }
    std::cout << sum << std::endl;
}

template class Matrix<int>;
template class Matrix<double>;
