#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include "../psvnAPI/global/priority_queue.hpp"

using namespace std;

int64_t nodes_expanded;

/**
 * A* (best-first search with delayed deduplication)
 * 
 * @param initState The initial state
 * @param h Heuristic
 */
int aStar(state_t *initState, int (*h)(state_t *)) {
    state_t state, child;
    int ruleid, g;
    ruleid_iterator_t iter;

    // Distance map
    state_map_t *distances = new_state_map();
    set_state_map(distances, initState, 0);

    // Queue of states to visit
    PriorityQueue<state_t> Q;
    Q.Add(0, 0, *initState);

    while (!Q.Empty()) {
        nodes_expanded++;

        // Current distance 
        g = Q.CurrentPriority();

        // Get the state with the lowest f-value
        state = Q.Top();
        Q.Pop();
        int *old_g = state_map_get(distances, &state);

        // If the state was not visited or if the new distance is lower
        if (old_g == NULL || g < *old_g) {
            // Add the state to the distance map
            set_state_add(distances, &state, g);

            // If the state is a goal state
            if (is_goal(&state)) {
                printf("Goal state found with distance %d\n", g);
                return g;
            }

            // Expand the state
            init_fwd_iter(&iter, &state);
            while ((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &state, &child);

                // Compute the distance to the child state
                int g_child = g + get_fwd_rule_cost(ruleid);
                int h_child = h(&child);  
                int gh_child = g_child + h_child;
                if (h_child < INT_MAX) {
                    // Add the state to the queue
                    Q.Add(gh_child, g_child, child);
                }
            }
        }
    }

    // No goal state found
    return -1;
}

int main(int argc, char **argv) {
    printf("A*\n");

    nodes_expanded = 0;
}
