#include "node.hpp"

using namespace std;

Node::Node(state_t newNode, Node *newParent, unsigned newG) {
  state = newNode;
  parent = newParent;
  g = newG;
}