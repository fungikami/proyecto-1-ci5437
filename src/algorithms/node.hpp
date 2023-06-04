#ifndef NODE_H
#define NODE_H

using namespace std;

/**
 * A node in the search tree
 */
class Node {
  public:
    state_t state;  // Node state
    Node *parent;   // Parent node
    unsigned g;     // Cost
    
    Node(state_t state, Node *parent, unsigned g);
};

#endif