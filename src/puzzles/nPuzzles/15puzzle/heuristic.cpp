// TO-DO: DO IT BETTEEEEEEEEEEEEEEEEEEEEH

#include <string>
#include <vector>

using namespace std;

// Global variables to store the PDBs and abstractions
vector<abstraction_t*> abstractions;
vector<state_map_t*> state_maps;

/**
 * Opens the PDBs and stores them in the global variables
 */
void init_heuristic() {
	// List of files
	vector<string> files = {"15puzzle_abs1", "15puzzle_abs2", "15puzzle_abs3"};

    // Open the PDBs
	for (unsigned int i = 0; i < files.size(); i++) {
		// Open the file (add .pdb)
		FILE *f = fopen((files[i] + ".pdb").c_str(), "r");
		if (f == NULL) {
			printf("Error: invalid PDB file.\n");
			return;
		}
		state_maps.push_back(read_state_map(f));
		fclose(f);

		// Open the abstraction
		abstractions.push_back(read_abstraction_from_file((files[i] + ".abst").c_str()));

		// Check if the PDBs and abstractions are valid
		if (state_maps[i] == NULL || abstractions[i] == NULL) {
			printf("Error: invalid PDB or abstraction.\n");
			state_maps.pop_back();
			abstractions.pop_back();
		}
	}
}

/**
 * Computes the heuristic value of a state
 * Additive PDBs
 * @param state The state to compute the heuristic value
 * @return The heuristic value of the state
 */
int heuristic(state_t *state) {
	// PDB values
	state_t *aux_state = new state_t;
	int sum = 0;

	// Compute the heuristic value
	for (unsigned int i = 0; i < abstractions.size(); i++) {
		// Get the state
		abstract_state(abstractions[i], state, aux_state);

		// Get the value
		sum += *state_map_get(state_maps[i], aux_state);

	}

	delete aux_state;

	return sum;
}