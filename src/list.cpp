#include "list.h"

#include <iostream>

template <typename T>
List<T>::List(): head(nullptr), tail(nullptr), before(nullptr), after(nullptr) {}

template <typename T>
List<T>::~List() {
    go_to_beg();
    while (!is_empty()) {
        del_after();
    }
}

template <typename T>
int List<T>::ins_before(Matrix<T>& m) {
    std::unique_ptr<Node<T>> new_node;
    try {
        new_node = std::make_unique<Node<T>>(m);
    }
    catch (...) {
        return -1;
    }

    Node<T> *raw = new_node.get();
    std::unique_ptr<Node<T>>& slot = before ? before->next :head;

    new_node->prev = before;
    new_node->next = std::move(slot);
    if (after) after->prev = raw;
    else tail = raw;
    slot = std::move(new_node);
    before = raw;
    return 0;
}

template <typename T>
int List<T>::ins_after(Matrix<T>& m) {
    std::unique_ptr<Node<T>> new_node;
    try {
        new_node = std::make_unique<Node<T>>(m);
    }
    catch (...) {
        return -1;
    }

    Node<T> *raw = new_node.get();
    std::unique_ptr<Node<T>>& slot = before ? before->next : head;

    new_node->prev = before;
    new_node->next = std::move(slot);
    if (after) after->prev = raw;
    else tail = raw;
    slot = std::move(new_node);
    after = raw;
    return 0;
}

template <typename T>
int List<T>::at_beg() {
    if (before == nullptr) return 1;
    else return 0;
}

template <typename T>
int List<T>::at_end() {
    if (after == nullptr) return 1;
    else return 0;
}

template <typename T>
int List<T>::is_empty() {
    if (head == nullptr) return 1;
    else return 0;
}

template <typename T>
int List<T>::del_before() {
    if (at_beg()) return -1;

    Node<T> *l = before->prev;
    std::unique_ptr<Node<T>>& slot = l ? l->next : head;
    std::unique_ptr<Node<T>> node_to_del = std::move(slot);
    slot = std::move(node_to_del->next);
    if (slot) slot->prev = l;
    else tail = l;
    before = l;
    return 0;
}

template <typename T>
int List<T>::del_after() {
    if (at_end()) return -1;

    Node<T> *l = after->prev;
    std::unique_ptr<Node<T>>& slot = l ? l->next : head;
    std::unique_ptr<Node<T>> node_to_del = std::move(slot);
    slot = std::move(node_to_del->next);
    if (slot) slot->prev = l;
    else tail = l;
    after = slot.get();
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
    after = before->next.get();
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
    before = nullptr;
    after = head.get();
}

template <typename T>
void List<T>::go_to_end() {
    after = nullptr;
    before = tail;
}

template <typename T>
void List<T>::show() {
    for (Node<T> *cur = head.get(); cur != nullptr; cur = cur->next.get()) {
        cur->data.show();
        if (cur == before) std::cout << " <-before";
        if (cur == after) std::cout << " <-after";
        std::cout << std::endl;
    }
}

template <typename T>
List<T>::List(const List<T>& other) : head(nullptr), tail(nullptr), before(nullptr), after(nullptr) {
    Node<T> *new_before = nullptr;
    Node<T> *new_after = nullptr;


    for (Node<T> *temp = other.head.get(); temp != nullptr; temp = temp->next.get()) {
        if (ins_before(temp->data) == -1) {
            go_to_beg();
            while (!is_empty()) del_after();
            return;
        }

        Node<T> *new_node = before;

        if (temp == other.before) new_before = new_node;
        if (temp == other.after) new_after = new_node;
    }

    before = new_before;
    after = new_after;

}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this == &other) return *this;

    go_to_beg();
    while (!is_empty()) del_after();

    Node<T> *new_before = nullptr;
    Node<T> *new_after = nullptr;

    for (Node<T> *temp = other.head.get(); temp != nullptr; temp = temp->next.get()) {
        if (ins_before(temp->data) == -1) {
            go_to_beg();
            while (!is_empty()) del_after();
            return *this;
        }

        Node<T> *new_node = before;

        if (temp == other.before) new_before = new_node;
        if (temp == other.after) new_after = new_node;
    }

    before = new_before;
    after = new_after;

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
    for (Node<T> *temp = head.get(); temp != nullptr; temp = temp->next.get()) {
        temp->data.sledMatrix();
    }
    return 0;
}

template class List<int>;
template class List<double>;
