#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

using namespace std;

#include <vector>
#include <string>
#include <stdio.h>

vector<string> state_to_string(state_t *state);

// Manhattan distance for N-puzzle
int manhattan(state_t *state, int n);
int get15puzzleManhattan(state_t *state);
int get24puzzleManhattan(state_t *state);

// PDBs


#endif
