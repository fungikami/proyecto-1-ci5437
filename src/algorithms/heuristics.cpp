/**
 * Heurístics
 */

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <algorithm>

/** 
 * Get state as string
 * @param state The state
 * @return The state as string
 */
vector<string> state_to_string(state_t *state) {
    string aux;
    vector<string> state_string;
    int n = sprint_state(st, MAX_STATE_LEN, state);

    for (int i = 0; i < n; i++) {
        if (st[i] == ' ') {
            state_string.push_back(aux);
            aux = "";
        } else {
            aux += st[i];
        }
    }

    return state_string;
}

// -------------------------------- MANHATTAN --------------------------------

/**
 * Manhattan distance for N-puzzle
 * @param state The state
 * @param n The size of the puzzle
 * @return The Manhattan distance
 */
int manhattan(state_t *state, int n) {
    int distance = 0;
    vector<string> st = state_to_string(state);

    for (int i = 0; i < st.size(); i++) {
        if (st[i] != "0") {
            int x = i / n;
            int y = i % n;
            int x_goal = i / n;
            int y_goal = i % n;
            distance += abs(x - x_goal) + abs(y - y_goal);
        }
    }

    return distance;
}

int get15puzzleManhattan(state_t *state) { return manhattan(state, 4); }

int get24puzzleManhattan(state_t *state) { return manhattan(state, 5); }

// -------------------------------- PDBs --------------------------------
