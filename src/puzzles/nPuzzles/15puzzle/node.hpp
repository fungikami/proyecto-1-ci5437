#ifndef NODE_HPP
#define NODE_HPP

using namespace std;

/**
 * A node in the search tree
 */
class Node {
  public:
    /** State represented by the node */
    state_t state;

    /** Parent node */
    Node *parent;

    /** Partial cost of the path from the root to this node */
    unsigned path_cost;

    Node(state_t state, Node *parent, unsigned path_cost);
};

// ola puse esto aquí por ahora pq estoy vuelta un qlo con el makefile
Node::Node(state_t state, Node *parent, unsigned path_cost) {
    this->state = state;
    this->parent = parent;
    this->path_cost = path_cost;
}

#endif