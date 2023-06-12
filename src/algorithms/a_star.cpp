#include "priority_queue.hpp"
using namespace std;

#define MAX_LINE_LENGTH 999

int64_t nodes_expanded;

/**
 * A* (best-first search with delayed deduplication)
 * 
 * @param init_state The initial state
 * @param h Heuristic
 */
int a_star(state_t *init_state, int (*h)(state_t*)) {
    state_t state, child;
    int ruleid, g, *old_g;
    ruleid_iterator_t iter;
    state_map_t *distances;
    PriorityQueue<state_t> frontier;

    // Distance map
    distances = new_state_map();
    state_map_add(distances, init_state, 0);

    // Min-priority queue on the f-value (g + h)
    frontier.Add(h(init_state), 0, *init_state);

    while (!frontier.Empty()) {
        nodes_expanded++;
        g = frontier.CurrentPriority();

        // Get the state with the lowest f-value
        state = frontier.Top();
        frontier.Pop();
        nodes_expanded++;

        // Current distance 
        g -= h(&state);

        // If the state is a goal state
        if (is_goal(&state)) {
            printf("Goal state found with distance %d, nodes expanded %ld\n", g, nodes_expanded);
            return g;
        }

        // Get the distance to the state
        old_g = state_map_get(distances, &state);

        // If the state was not visited or if the new distance is lower
        if (old_g == NULL || g <= *old_g) {
            // Update the distance
            state_map_add(distances, &state, g);

            // Expand the state
            init_fwd_iter(&iter, &state);
            while ((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &state, &child);

                // Compute the distance to the child state
                int h_child = h(&child); 
                if (h_child < INT_MAX) {
                    // Add the state to the queue with the new distance
                    int g_child = g + get_fwd_rule_cost(ruleid);
                    int f_child = g_child + h_child;
                    frontier.Add(f_child, g_child, child);
                }
            }
        }
    }

    // No goal state found
    printf("No goal state found, nodes expanded %ld\n", nodes_expanded);
    return -1;
}

int main(int argc, char **argv) {
    printf("A*\n");
    char str[MAX_LINE_LENGTH + 1], *filename;
    ssize_t n; 
    state_t state; 
    
    for (;;) {
        if (fgets(str, sizeof str, stdin) == NULL) return 0; 

        n = read_state(str, &state);
        if (n <= 0) {
            printf("Error: invalid state.\n");
            continue; 
        }

        nodes_expanded = 0;
        int d = a_star(&state, heuristic);
    }

    return 0;
}
