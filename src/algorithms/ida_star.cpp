#include <iostream>
#include <algorithm>
#include <utility>      // std::pair
#include "node.hpp"
#include "priority_queue.hpp"

using namespace std;

#define MAX_LINE_LENGTH 999

unsigned long int nodes_expanded;

/**
 * Visits the state and its children up to a certain depth
 * 
 * @param n The node to visit
 * @param bound The maximum depth
 * @param hist The history of the state
 * @param h Heuristic function, returns the heuristic value of a state
 * @return A pair containing the goal node and its cost
 */
pair<Node *, unsigned> f_bounded_dfs_visit(Node *n, unsigned bound, int hist, int (*h)(state_t*)) {
    int ruleid;
    unsigned t;
    ruleid_iterator_t iter;
    state_t child;  

    // If the f-value is greater than the bound, return the f-value
    unsigned f = n->path_cost + h(&n->state);
    if (f > bound) return make_pair(nullptr, f);

    // If the state is a goal state, return the node
    if (is_goal(&n->state)) return make_pair(n, n->path_cost);

    // Expand the node
    nodes_expanded++;
    t = INT_MAX;
    init_fwd_iter(&iter, &n->state);
    while ((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid, &n->state, &child);

        // If the state was already visited, skip it
        if (!fwd_rule_valid_for_history(hist, ruleid)) continue;

        // Create a new node for the child
        Node m(child, n, n->path_cost + get_fwd_rule_cost(ruleid));

        // Visit the child node
        pair<Node *, unsigned> p = f_bounded_dfs_visit(&m, bound, next_fwd_history(hist, ruleid), h);
        if (p.first != nullptr) return p;
        t = min(t, p.second);
    }

    return make_pair(nullptr, t);
}

/**
 * IDA* algorithm
 * 
 * @param state The initial state
 * @param h Heuristic
 * @return The goal node
 */
Node ida_star(state_t *state, int (*h)(state_t*)) {
    Node root(*state, nullptr, 0);
    pair<Node *, int> p;
    unsigned long int bound = h(state);

    for(;;) {
        printf("Exploring with depth bound %ld\n", bound);
        p = f_bounded_dfs_visit(&root, bound, init_history, h);
        if (p.first != nullptr) return *p.first;
        bound = p.second;
    }
}

int main(int argc, char **argv) {
    printf("IDA*\n");
    char str[MAX_LINE_LENGTH + 1], *filename;
    ssize_t n; 
    state_t state; 
    clock_t start, end;
    float time;

    init_heuristic();

    for (;;) {
        if (fgets(str, sizeof str, stdin) == nullptr) return 0; 

        n = read_state(str, &state);
        if (n <= 0) {
            printf("Error: invalid state.\n");
            continue; 
        }

        nodes_expanded = 0;
        start = clock();
        Node node = ida_star(&state, heuristic);
        end = clock();

        time = (float)(end - start) / CLOCKS_PER_SEC;
        printf("Goal state found with distance %d, nodes expanded %ld, time %f\n", node.path_cost, nodes_expanded, time);
    }

    return 0;
}
