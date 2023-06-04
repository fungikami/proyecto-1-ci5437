#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <limits.h>

#include "node.hpp"
#include "../psvnAPI/global/priority_queue.hpp"

using namespace std;

int64_t nodesExpanded;

/**
 * Visits the state and its children up to a certain depth
 * 
 * @param n The node to visit
 * @param bound The maximum depth
 * @return A pair containing the goal node and its cost
 */
pair<Node *, unsigned> f_bounded_dfs_visit(Node *n, unsigned bound, int hist) {
    int t, ruleid;
    ruleid_iterator_t iter;
    state_t child;  

    // If the f-value is greater than the bound, return the f-value
    unsigned f = n->g + h(&n->state);
    if (f > bound) return make_pair(NULL, f);

    // If the state is a goal state, return the node
    if (is_goal(&n->state)) return make_pair(n, n->g);

    // Expand the node
    ++nodesExpanded;
    t = INT_MAX;
    init_fwd_iter(&iter, &n->state);
    while ((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid, &n->state, &child);

        // If the state was already visited, skip it
        if (!fwd_rule_valid_for_history(hist, ruleid)) continue;

        // Create a new node for the child
        Node m(child, n, n->g + get_fwd_rule_cost(ruleid));

        // Visit the child node
        pair<Node *, unsigned> p = f_bounded_dfs_visit(&m, bound);
        if (p.first != NULL) return p;
        t = min(t, p.second);
    }

    return make_pair(NULL, t);
}

/**
 * IDA* algorithm
 * 
 * @param state The initial state
 * @return The goal node
 */
Node idaStar(state_t *state) {
    Node root(state, NULL, 0);
    pair<Node *, int> p;
    unsigned bound = h(state);

    while (1) {
        p = f_bounded_dfs_visit(&root, bound, init_history);
        if (p.first != NULL) return *p.first;
        bound = p.second;
    }
}

int main(int argc, char **argv) {
    printf("IDA*\n");

    nodesExpanded = 0;

}