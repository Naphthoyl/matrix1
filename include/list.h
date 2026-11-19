#ifndef LIST_H
#define LIST_H

#include "matrix.h"
#include "node.h"

template <typename T>
class List {
    std::unique_ptr<Node<T>> head;
    Node<T> *tail;
    Node<T> *before, *after;

public:
    List();
    ~List();
    List(const List& other);
    List& operator=(const List& other);

    int ins_before(Matrix<T>& m);
    int ins_after(Matrix<T>& m);
    int at_beg();
    int at_end();
    int is_empty();
    int del_before();
    int del_after();
    int get_before(Matrix<T>& num);
    int get_after(Matrix<T>& num);
    int set_before(Matrix<T>& num);
    int set_after(Matrix<T>& num);
    int step_forward();
    int step_backward();
    void go_to_beg();
    void go_to_end();
    void show();

    int sum(Matrix<T>& result);
    int mul(Matrix<T>& result);
    int sled();
};

extern template class List<int>;
extern template class List<double>;

#endif 
