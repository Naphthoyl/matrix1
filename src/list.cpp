#include "list.h"

#include <iostream>

template <typename T>
List<T>::List() {
    base.prev = &base;
    base.next = &base;
    before = &base;
    after = &base;
}

template <typename T>
List<T>::~List() {
    go_to_beg();
    while (!is_empty()) {
        del_after();
    }
}

template <typename T>
int List<T>::ins_before(Matrix<T>& m) {
    Node<T> *new_node = nullptr;
    try {
        new_node = new Node<T>(m);
    }
    catch (...) {
        return -1;
    }

    new_node->prev = before;
    new_node->next = after;
    before->next = new_node;
    after->prev = new_node;
    before = new_node;
    return 0;
}

template <typename T>
int List<T>::ins_after(Matrix<T>& m) {
    Node<T> *new_node = nullptr;
    try {
        new_node = new Node<T>(m);
    }
    catch (...) {
        return -1;
    }

    new_node->prev = before;
    new_node->next = after;
    before->next = new_node;
    after->prev = new_node;
    after = new_node;
    return 0;
}

template <typename T>
int List<T>::at_beg() {
    if (before == &base) return 1;
    else return 0;
}

template <typename T>
int List<T>::at_end() {
    if (after == &base) return 1;
    else return 0;
}

template <typename T>
int List<T>::is_empty() {
    if (base.next == &base) return 1;
    else return 0;
}

template <typename T>
int List<T>::del_before() {
    if (at_beg()) return -1;

    Node<T> *del = before;
    Node<T> *l = del->prev;
    Node<T> *r = del->next;
    l->next = r;
    r->prev = l;
    before = l;
    delete del;
    return 0;
}

template <typename T>
int List<T>::del_after() {
    if (at_end()) return -1;

    Node<T> *del = after;
    Node<T> *l = del->prev;
    Node<T> *r = del->next;
    l->next = r;
    r->prev = l;
    after = r;
    delete del;
    return 0;
}

template <typename T>
int List<T>::get_before(Matrix<T>& num) {
    if (at_beg()) return -1;

    num = before->data;
    return 0;
}

template <typename T>
int List<T>::get_after(Matrix<T>& num) {
    if (at_end()) return -1;

    num = after->data;
    return 0;
}

template <typename T>
int List<T>::set_before(Matrix<T>& num) {
    if (at_beg()) return -1;

    before->data = num;
    return 0;
}

template <typename T>
int List<T>::set_after(Matrix<T>& num) {
    if (at_end()) return -1;

    after->data = num;
    return 0;
}

template <typename T>
int List<T>::step_forward() {
    if (at_end()) return -1;

    before = after;
    after = before->next;
    return 0;
}

template <typename T>
int List<T>::step_backward() {
    if (at_beg()) return -1;

    after = before;
    before = after->prev;
    return 0;
}

template <typename T>
void List<T>::go_to_beg() {
    before = &base;
    after = before->next;
}

template <typename T>
void List<T>::go_to_end() {
    after = &base;
    before = after->prev;
}

template <typename T>
void List<T>::show() {
    Node<T>* cur = base.next;
    while (cur != &base) {
        cur->data.show();
        if (cur == before) std::cout << " <-before";
        if (cur == after) std::cout << " <-after";
        cur = cur->next;
        std::cout << std::endl;
    }
}

template <typename T>
List<T>::List(const List<T>& other) {
    base.prev = &base;
    base.next = &base;
    before = &base;
    after = &base;

    Node<T> *new_before = &base;
    Node<T> *new_after = &base;

    go_to_end();

    for (Node<T> *temp = other.base.next; temp != &other.base; temp = temp->next) {
        if (ins_before(temp->data) == -1) {
            go_to_beg();
            while (!is_empty()) del_after();
            return;
        }

        Node<T> *new_node = before;

        if (temp == other.before) new_before = new_node;
        if (temp == other.after) new_after = new_node;
    }

    if (other.before == &other.base) before = &base;
    else before = new_before;

    if (other.after == &other.base) after = &base;
    else after = new_after;
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this == &other) return *this;

    go_to_beg();
    while (!is_empty()) del_after();

    base.prev = &base;
    base.next = &base;
    before = &base;
    after = &base;

    Node<T> *new_before = &base;
    Node<T> *new_after = &base;

    go_to_end();

    for (Node<T> *temp = other.base.next; temp != &other.base; temp = temp->next) {
        if (ins_before(temp->data) == -1) {
            go_to_beg();
            while (!is_empty()) del_after();
            return *this;
        }

        Node<T> *new_node = before;

        if (temp == other.before) new_before = new_node;
        if (temp == other.after) new_after = new_node;
    }

    if (other.before == &other.base) before = &base;
    else before = new_before;

    if (other.after == &other.base) after = &base;
    else after = new_after;

    return *this;
}

template <typename T>
int List<T>::sum(Matrix<T>& result) {
    if (at_beg() || at_end()) return -1;

    result = before->data + after->data;
    return 0;
}

template <typename T>
int List<T>::mul(Matrix<T>& result) {
    if (at_beg() || at_end()) return -1;

    result = before->data * after->data;
    return 0;
}

template <typename T>
int List<T>::sled() {
    for (Node<T> *temp = base.next; temp != &base; temp = temp->next) {
        temp->data.sledMatrix();
    }
    return 0;
}

template class List<int>;
template class List<double>;
