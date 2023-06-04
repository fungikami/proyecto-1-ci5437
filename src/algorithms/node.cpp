#include "node.hpp"

using namespace std;

Node::Node(state_t state, Node *parent, unsigned path_cost) {
    this->state = state;
    this->parent = parent;
    this->path_cost = path_cost;
}