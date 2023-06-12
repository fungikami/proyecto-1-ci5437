// TO-DO: DO IT BETTEEEEEEEEEEEEEEEEEEEEH

#include <string>
#include <vector>
#include "../../../algorithms/pdb.hpp"

using namespace std;

// Global variables to store the PDBs and abstractions
vector<PDB> pdbs;

/**
 * Opens the PDBs and stores them in the global variables
 */
void init_heuristic() {
    // List of files
    vector<string> files = {"15puzzle_abs1", "15puzzle_abs2", "15puzzle_abs3"};

    // Open the PDBs
    for (unsigned i = 0; i < files.size(); i++) pdbs.emplace_back(files[i]);
}

/**
 * Computes the heuristic value of a state
 * Additive PDBs
 * 
 * @param state The state to compute the heuristic value
 * @return The heuristic value of the state
 */
int heuristic(state_t *state) {
    int h = 0;
    for (unsigned i = 0; i < pdbs.size(); i++) h += pdbs[i].get_cost(state);

    return h;
}
