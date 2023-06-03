#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <signal.h>

using namespace std;

long int numStates = 1; // The number of states visited at each depth

void timeout(int signum) {
    printf("Time limit reached\n");
    printf("Number of states visited: %ld\n", numStates);
    exit(0);
}

/**
 * Breadth-First Search algorithm implementation, with and without pruning
 * 
 * @param initialState The initial state to start from
 * @param withPruning Whether to use pruning or not
 */
void bfs(state_t initialState, bool withPruning = false) {
    state_t currentState, child;
    queue<state_t> frontier;
    queue<state_t> nextFrontier;

    int ruleid, currentDepth = 0;
    ruleid_iterator_t iter;

    // Prints the header of the table
    printf("Depth,Number of states\n");
    printf("%d,%ld\n", currentDepth, numStates);

    // While there are states left to visit
    frontier.push(initialState);
    while (!frontier.empty()) {
        // Extract the first state in the queue
        currentState = frontier.front();
        frontier.pop();

        // Iterate over every child of the current state
        init_fwd_iter(&iter, &currentState);
        while ((ruleid = next_ruleid(&iter)) >= 0) {
            apply_fwd_rule(ruleid, &currentState, &child);

            nextFrontier.push(child);
            numStates++;
        }
        
        // Verifies if all the states in a depth have been visited
        if (frontier.empty()) {
            frontier = nextFrontier;
            nextFrontier = queue<state_t>();
            currentDepth++;

            // Prints a table with the number of states visited at each depth
            printf("%d,%ld\n", currentDepth, numStates);
        }
    }
}

int main(int argc, char const *argv[]) {
    signal(SIGTERM, timeout);

    // Generates an initial state (the goal state in this case)
    state_t goalState;
    int goal_num;
    first_goal_state(&goalState, &goal_num);

    // Checks arguments to see if it's using pruning
    bool withPruning = argc > 1 ? atoi(argv[1]) : false;

    bfs(goalState);
}
