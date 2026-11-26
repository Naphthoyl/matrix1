#include "node.h"

template <typename T>
Node<T>::Node() : data(), prev(nullptr), next(nullptr) {}

template <typename T>
Node<T>::Node(Matrix<T>& m) : data(m), prev(nullptr), next(nullptr) {}

template class Node<int>;
template class Node<double>;