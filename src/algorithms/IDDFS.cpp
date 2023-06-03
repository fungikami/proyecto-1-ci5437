#include <vector>
#include <signal.h>

using namespace std;

long int numStates = 0; // The number of states visited at each depth

void timeout(int signum) {
    printf("Time limit reached\n");
    printf("Number of states visited: %ld\n", numStates);
    exit(0);
}

/**
 * Visits the state and its children up to a certain depth
 * 
 * @param state The state to explore
 * @param depth The current depth
 * @param bound The maximum depth to visit
 * @param numStates A vector containing the number of states visited at each depth
 * @param hist The history of the state
 */
void bounded_dfs_visit(
    state_t *state, 
    int depth, 
    int bound, 
    long int *numStates,
    int hist
) {
    state_t child;
    int ruleid;
    ruleid_iterator_t iter;

    // Base case
    if (depth > bound) return;

    // if (depth == bound)
        (*numStates)++;

    // Apply rules
    init_fwd_iter(&iter, state);
    while ((ruleid = next_ruleid(&iter)) >= 0) {

        // If pruning, check if the state has been visited
        if (hist!=-1 && fwd_rule_valid_for_history(hist, ruleid) == 0) continue;

        apply_fwd_rule(ruleid, state, &child);

        // If pruning, update the history
        if (hist!=-1) {
            int hist_child = next_fwd_history(hist, ruleid);
            bounded_dfs_visit(&child, depth + 1, bound, numStates, hist_child);
        }

        bounded_dfs_visit(&child, depth + 1, bound, numStates, hist);
    }
}

/**
 * Iterative Deepening Depth-First Search algorithm implementation
 *
 * @param initialState The initial state to start from
 */
void iddfs(state_t initialState, int withPruning = 0) {
    // Sets the initial bound
    int bound = 0;

    // If pruning, initialize the history, else -1
    int hist = withPruning ? init_history : -1;

    printf("Depth,Number of states,Branching factor\n");

    for (;;) {
        bounded_dfs_visit(&initialState, 0, bound, &numStates, hist);
        printf("%d,%ld\n", bound, numStates);
        bound++;
        numStates = 0;
    }
}

int main(int argc, char const *argv[]) {
    signal(SIGTERM, timeout);

    // Generates an initial state (the goal state in this case)
    int goal_num;
    state_t goalState;
    first_goal_state(&goalState, &goal_num);

    // Checks arguments to see if it's using pruning
    bool withPruning = argc > 1 ? atoi(argv[1]) : false;

    iddfs(goalState, withPruning);
}
