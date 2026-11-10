#ifndef LIST_H
#define LIST_H

#include "matrix.h"
#include "node.h"

class List {
    Node base;
    Node *before, *after;

public:
    List();
    ~List();
    List(const List& other);
    List& operator=(const List& other);

    int ins_before(Matrix& m);
    int ins_after(Matrix& m);
    int at_beg();
    int at_end();
    int is_empty();
    int del_before();
    int del_after();
    int get_before(Matrix& num);
    int get_after(Matrix& num);
    int set_before(Matrix& num);
    int set_after(Matrix& num);
    int step_forward();
    int step_backward();
    void go_to_beg();
    void go_to_end();
    void show();

    int sum(Matrix& result);
    int mul(Matrix& result);
    int sled();
};

#endif 
