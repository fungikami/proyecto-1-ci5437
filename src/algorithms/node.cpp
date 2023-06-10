#include "node.hpp"

using namespace std;

/**
 * Node constructor
 * 
 * @param state The state
 * @param parent The parent node
 * @param path_cost The cost of the path from the initial state to this node
 */
Node::Node(state_t state, Node *parent, unsigned path_cost) {
    this->state = state;
    this->parent = parent;
    this->path_cost = path_cost;
}