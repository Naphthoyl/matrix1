#ifndef NODE_H
#define NODE_H

#include "matrix.h"


template <typename T>
class List;

template <typename T>
class Node {
    Matrix<T> data;
    Node *prev, *next;
    friend class List<T>;

public:
    Node();
    Node(Matrix<T>& m);
};

extern template class Node<int>;
extern template class Node<double>;

#endif
