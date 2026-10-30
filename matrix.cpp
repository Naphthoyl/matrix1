#include <iostream>
#include <fstream>

class Matrix {
private:
    int n;
    int** a;
    friend class List;
    friend class Node;

public:
    Matrix();
    Matrix(int size);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    void input(std::ifstream& fin);
    void show();
    Matrix operator+(const Matrix& other);
    Matrix operator*(const Matrix& other);
    void sledMatrix();
};

class Node {
    Matrix data;
    Node *prev, *next;
    friend class List;

public:
    Node();
    Node(Matrix& m);
};

class List {
    Node base;
    Node *before, *after;

public:
    List();
    ~List();

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

    List(const List& other);
    List& operator=(const List& other);

    int sum(Matrix& result);
    int mul(Matrix& result);
    int sled();
};


// ---------------- Реализация методов Matrix ----------------

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

// ---------------- Реализация методов Node ----------------

Node::Node() : data(), prev(nullptr), next(nullptr) {}

Node::Node(Matrix& m) : data(m), prev(nullptr), next(nullptr) {}

// ---------------- Реализация методов List ----------------

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

// ---------------- main ----------------

int main() {
    std::ifstream fin("text.txt");
    if (!fin.is_open()) {
        std::cout << "error" << std::endl;
        return -1;
    }

    int n = 0; // кол-во матриц
    fin >> n;

    if (n <= 0) {
        std::cout << "error" << std::endl;
        return -2;
    }

    List ob1;

    int n1 = 0;
    for (int k = 0; k < n; k++) {
        fin >> n1;
        Matrix a(n1);
        a.input(fin);
        ob1.ins_before(a);
    }

    ob1.sled();
    ob1.show();

    return 0;
}
