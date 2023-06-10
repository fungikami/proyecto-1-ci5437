#include <signal.h>
#include <stdio.h>
#include <vector>

using namespace std;

// The number of states visited at each depth
long int n_states = 0;

/**
 * Signal handler that prints a message to stderr indicating that the time limit
 * has been reached and the number of states visited, and then exits the program.
 * 
 * @param signum The signal number
 */
void timeout(int signum) {
    fprintf("last depth,%ld\n", n_states);

    // Prints to stderr so that it doesn't interfere with the output
    fprintf(stderr, "Time limit reached\n");
    fprintf(stderr, "Number of states visited: %ld\n", n_states);
    exit(0);
}

/**
 * Visits the state and its children up to a certain depth
 * 
 * @param state The state to explore
 * @param depth The current depth
 * @param bound The maximum depth to visit
 * @param n_states A vector containing the number of states visited at each depth
 */
void bounded_dfs_visit(
    state_t *state, 
    int depth, 
    int bound, 
    long int *n_states
) {
    state_t child;
    int ruleid;
    ruleid_iterator_t iter;

    (*n_states)++;

    // Base case
    if (depth == bound) return;

    // Apply rules
    init_bwd_iter(&iter, state);

    while ((ruleid = next_ruleid(&iter)) >= 0) {
        apply_bwd_rule(ruleid, state, &child);
        bounded_dfs_visit(&child, depth + 1, bound, n_states);
    }
}

/**
 * Visits the state and its children up to a certain depth, pruning the
 * children that have already been visited
 * 
 * @param state The state to explore
 * @param depth The current depth
 * @param bound The maximum depth to visit
 * @param n_states A vector containing the number of states visited at each depth
 * @param hist The history of the state
 */
void bounded_dfs_visit_with_pruning(
    state_t *state, 
    int depth, 
    int bound, 
    long int *n_states,
    int hist
) {
    state_t child;
    int ruleid;
    ruleid_iterator_t iter;

    (*n_states)++;

    // Base case
    if (depth == bound) return;


    // Apply rules
    init_bwd_iter(&iter, state);

    while ((ruleid = next_ruleid(&iter)) >= 0) {
        if (!bwd_rule_valid_for_history(hist, ruleid)) continue;

        // Generate the child state and update the history
        apply_bwd_rule(ruleid, state, &child);

        bounded_dfs_visit_with_pruning(
            &child,
            depth + 1,
            bound,
            n_states,
            next_bwd_history(hist, ruleid)
        );
    }
}

/**
 * Iterative Deepening Depth-First Search algorithm implementation
 *
 * @param initialState The initial state to start from
 */
void iddfs(state_t initialState, bool pruning = false) {
    // Sets the initial bound
    int bound = 1;

    for (;;) {
        if (pruning) {
            int hist = init_history;
            bounded_dfs_visit_with_pruning(
                &initialState,
                0,
                bound,
                &n_states,
                hist
            );
        } else {
            bounded_dfs_visit(&initialState, 0, bound, &n_states);
        }

        // Prints the number of states visited at each depth
        printf("%d,%ld\n", bound, n_states);

        // Augments the bound and resets the number of states visited
        bound++;
        n_states = 0;
    }
}

int main(int argc, char const *argv[]) {
    signal(SIGTERM, timeout);

    // Generates an initial state (the goal state in this case)
    int goal_num;
    state_t goal_state;
    first_goal_state(&goal_state, &goal_num);

    // Checks arguments to see if it's using pruning
    bool pruning = argc > 1 ? true : false;

    // Header of the table
    printf("Depth,Number of states\n");

    iddfs(goal_state, pruning);
}
