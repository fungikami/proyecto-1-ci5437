#include <signal.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <queue>

using namespace std;

// The number of states visited at each depth
long int n_states = 1;

/**
 * Signal handler that prints a message to stderr indicating that the time limit
 * has been reached and the number of states visited, and then exits the program.
 * 
 * @param signum The signal number
 */
void timeout(int signum) {
    // Prints to stderr so that it doesn't interfere with the output
    fprintf(stderr, "Time limit reached\n");
    fprintf(stderr, "Number of states visited: %ld\n", n_states);
    exit(0);
}

// TODO: Struct to store a state and its hist
// struct state_hist {
//     state_t state;
//     int hist;
// };

/**
 * Breadth-First Search algorithm implementation, with and without pruning
 * 
 * @param initialState The initial state to start from
 * @param pruning Whether to use pruning or not
 */
void bfs(state_t initialState, bool pruning = false) {
    state_t current_state, child;
    queue<state_t> frontier;
    queue<state_t> next_frontier;

    int ruleid, current_depth = 0;
    ruleid_iterator_t iter;

    // Header of the table
    printf("| Depth | Number of states |\n");
    printf("| ----: | ----------------:|\n");

    int hist = init_history;

    // While there are states left to visit
    frontier.push(initialState);
    while (!frontier.empty()) {
        // Extract the first state in the queue
        current_state = frontier.front();
        frontier.pop();

        // Iterate over every child of the current state
        init_fwd_iter(&iter, &current_state);
        while ((ruleid = next_ruleid(&iter)) >= 0) {
            
            if (pruning) {
                // If the state has already been visited, skip it
                if (fwd_rule_valid_for_history(hist, ruleid) == 0) {
                    continue;
                }
            }

            apply_fwd_rule(ruleid, &current_state, &child);

            // Generates the history of the child
            hist = next_fwd_history(hist, ruleid);

            next_frontier.push(child);
            n_states++;
        }
        
        // Verifies if all the states in a depth have been visited
        if (frontier.empty()) {
            frontier = next_frontier;
            next_frontier = queue<state_t>();
            current_depth++;

            // Prints a table with the number of states visited at each depth
            printf("| %d | %ld |\n", current_depth, n_states);
        }
    }
}

int main(int argc, char const *argv[]) {
    signal(SIGTERM, timeout);

    // Generates an initial state (the goal state in this case)
    state_t goal_state;
    int goal_num;
    first_goal_state(&goal_state, &goal_num);

    // Checks arguments to see if it's using pruning
    bool pruning = argc > 1 ? true : false;

    bfs(goal_state);
}
