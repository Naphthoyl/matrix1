#include "list.h"

#include <iostream>

List::List() {
    base.prev = &base;
    base.next = &base;
    before = &base;
    after = &base;
}

List::~List() {
    go_to_beg();
    while (!is_empty()) {
        del_after();
    }
}

int List::ins_before(Matrix& m) {
    Node *new_node = nullptr;
    try {
        new_node = new Node(m);
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

int List::ins_after(Matrix& m) {
    Node *new_node = nullptr;
    try {
        new_node = new Node(m);
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

int List::at_beg() {
    if (before == &base) return 1;
    else return 0;
}

int List::at_end() {
    if (after == &base) return 1;
    else return 0;
}

int List::is_empty() {
    if (base.next == &base) return 1;
    else return 0;
}

int List::del_before() {
    if (at_beg()) return -1;

    Node *del = before;
    Node *l = del->prev;
    Node *r = del->next;
    l->next = r;
    r->prev = l;
    before = l;
    delete del;
    return 0;
}

int List::del_after() {
    if (at_end()) return -1;

    Node *del = after;
    Node *l = del->prev;
    Node *r = del->next;
    l->next = r;
    r->prev = l;
    after = r;
    delete del;
    return 0;
}

int List::get_before(Matrix& num) {
    if (at_beg()) return -1;

    num = before->data;
    return 0;
}

int List::get_after(Matrix& num) {
    if (at_end()) return -1;

    num = after->data;
    return 0;
}

int List::set_before(Matrix& num) {
    if (at_beg()) return -1;

    before->data = num;
    return 0;
}

int List::set_after(Matrix& num) {
    if (at_end()) return -1;

    after->data = num;
    return 0;
}

int List::step_forward() {
    if (at_end()) return -1;

    before = after;
    after = before->next;
    return 0;
}

int List::step_backward() {
    if (at_beg()) return -1;

    after = before;
    before = after->prev;
    return 0;
}

void List::go_to_beg() {
    before = &base;
    after = before->next;
}

void List::go_to_end() {
    after = &base;
    before = after->prev;
}

void List::show() {
    Node* cur = base.next;
    while (cur != &base) {
        cur->data.show();
        if (cur == before) std::cout << " <-before";
        if (cur == after) std::cout << " <-after";
        cur = cur->next;
        std::cout << std::endl;
    }
}

List::List(const List& other) {
    base.prev = &base;
    base.next = &base;
    before = &base;
    after = &base;

    Node *new_before = &base;
    Node *new_after = &base;

    go_to_end();

    for (Node *temp = other.base.next; temp != &other.base; temp = temp->next) {
        if (ins_before(temp->data) == -1) {
            go_to_beg();
            while (!is_empty()) del_after();
            return;
        }

        Node *new_node = before;

        if (temp == other.before) new_before = new_node;
        if (temp == other.after) new_after = new_node;
    }

    if (other.before == &other.base) before = &base;
    else before = new_before;

    if (other.after == &other.base) after = &base;
    else after = new_after;
}

List& List::operator=(const List& other) {
    if (this == &other) return *this;

    go_to_beg();
    while (!is_empty()) del_after();

    base.prev = &base;
    base.next = &base;
    before = &base;
    after = &base;

    Node *new_before = &base;
    Node *new_after = &base;

    go_to_end();

    for (Node *temp = other.base.next; temp != &other.base; temp = temp->next) {
        if (ins_before(temp->data) == -1) {
            go_to_beg();
            while (!is_empty()) del_after();
            return *this;
        }

        Node *new_node = before;

        if (temp == other.before) new_before = new_node;
        if (temp == other.after) new_after = new_node;
    }

    if (other.before == &other.base) before = &base;
    else before = new_before;

    if (other.after == &other.base) after = &base;
    else after = new_after;

    return *this;
}

int List::sum(Matrix& result) {
    if (at_beg() || at_end()) return -1;

    result = before->data + after->data;
    return 0;
}

int List::mul(Matrix& result) {
    if (at_beg() || at_end()) return -1;

    result = before->data * after->data;
    return 0;
}

int List::sled() {
    for (Node *temp = base.next; temp != &base; temp = temp->next) {
        temp->data.sledMatrix();
    }
    return 0;
}
