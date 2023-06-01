#include <vector>
#include <ctime>

#define TIME_LIMIT 900

using namespace std;

clock_t startTimer;

/**
 * Visits the state and its children up to a certain depth
 * @param state     The state to visit
 * @param depth     The current depth
 * @param bound     The maximum depth to visit
 * @param numStates A vector containing the number of states visited at each depth
 * @param hist      The history of the state
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

    // Check if the time limit has been reached
    if ((double)(clock() - startTimer) / CLOCKS_PER_SEC >= TIME_LIMIT) {
        printf("Time limit reached\n");
        exit(0);
    }
    
    if (depth > bound) return;

    if (depth == bound) (*numStates)++;

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
 * Iterative Deepening Depth-First Search
 * @param state The state to start from
 */
void IDDFS(state_t *state, int withPruning = 0) {
    int bound = 0;          // The current bound
    long int numStates = 0; // The number of states visited at each depth

    // If pruning, initialize the history, else -1
    int hist = withPruning ? init_history : -1;

    printf("IDDFS\nDepth\t\t#States\t\tBranching Factor\n");

    while (1) {
        bounded_dfs_visit(state, 0, bound, &numStates, hist);
        printf("%d\t\t%ld\n", bound, numStates);
        bound++;
        numStates = 0;
    }
}

int main(int argc, char const *argv[]) {
    int d;
    state_t goal;
    first_goal_state(&goal, &d);

    // Check arguments if is using pruning
    int withPruning = argc > 1 ? atoi(argv[1]) : 0;

    // Start the timer
    startTimer = clock();

    IDDFS(&goal, withPruning);
}