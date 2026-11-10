#include "node.h"

Node::Node() : data(), prev(nullptr), next(nullptr) {}

Node::Node(Matrix& m) : data(m), prev(nullptr), next(nullptr) {}
