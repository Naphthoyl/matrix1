#ifndef NODE_H
#define NODE_H

#include "matrix.h"

class Node {
    Matrix data;
    Node *prev, *next;
    friend class List;

public:
    Node();
    Node(Matrix& m);
};

#endif
