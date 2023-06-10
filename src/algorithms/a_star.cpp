#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include "priority_queue.hpp"

#define MAX_LINE_LENGTH 999

using namespace std;

int64_t nodes_expanded;

/**
 * A* (best-first search with delayed deduplication)
 * 
 * @param init_state The initial state
 * @param h Heuristic
 */
int a_star(state_t *init_state, unsigned (*h)(state_t)) {
    state_t state, child;
    int ruleid, g;
    ruleid_iterator_t iter;

    // Distance map
    state_map_t *distances = new_state_map();
    state_map_add(distances, init_state, 0);

    // Min-priority queue on the f-value (g + h)
    PriorityQueue<state_t> frontier;
    frontier.Add(h(*init_state), 0, *init_state);

    while (!frontier.Empty()) {
        nodes_expanded++;

        // Current distance 
        g = frontier.CurrentPriority();

        // Get the state with the lowest f-value
        state = frontier.Top();
        frontier.Pop();

        // If the state is a goal state
        if (is_goal(&state)) {
            printf("Goal state found with distance %d\n", g);
            return g;
        }

        int *old_g = state_map_get(distances, &state);

        // If the state was not visited or if the new distance is lower
        if (old_g == NULL || g < *old_g) {
            // Update the distance
            state_map_add(distances, &state, g);

            // Expand the state
            init_fwd_iter(&iter, &state);
            while ((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &state, &child);

                // Compute the distance to the child state
                int g_child = g + get_fwd_rule_cost(ruleid);
                int h_child = h(child);  
                int f_child = g_child + h_child;

                if (h_child < INT_MAX) {
                    // Add the state to the queue
                    frontier.Add(f_child, g_child, child);
                }
            }
        }

        // Freeeeee
        
    }

    // No goal state found
    return -1;
}

int main(int argc, char **argv) {
    printf("A*\n");

    // VARIABLES FOR INPUT
    char str[MAX_LINE_LENGTH + 1];
    ssize_t n; 
    state_t state; 

    // Read the state. 
    // Ex: 7 15 8 2 13 6 3 12 11 0 4 10 9 5 1 14 
    printf("Insert a state followed by ENTER: ");
    if (fgets(str, sizeof str, stdin) == NULL) {
        printf("Error: empty input line.\n");
        return 0; 
    }

    str[strlen(str) - 1] = '\0';
    
    printf("State entered: " );
    printf("%s\n", str);

    // TO-DO BETTEHH Open the PDBs
    openPDBs();

    // Convert the string to a state
    n = read_state(str, &state);
    if (n <= 0) {
        printf("Error: invalid state entered.\n");
        return 0; 
    }

    nodes_expanded = 0;
    int distance = a_star(&state, heuristic);
    printf("Distance: %d\n", distance);
    printf("Nodes expanded: %ld\n", nodes_expanded);

    return 0;
}
