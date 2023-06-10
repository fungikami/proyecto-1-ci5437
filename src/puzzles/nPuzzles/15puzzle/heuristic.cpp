// TO-DO: DO IT BETTEEEEEEEEEEEEEEEEEEEEH

state_map_t *map1;
abstraction_t *abs1;
state_t state1;

state_map_t *map2;
abstraction_t *abs2;
state_t state2;

state_map_t *map3;
abstraction_t *abs3;
state_t state3;

/**
 * Opens the PDBs and stores them in the global variables
 */
void openPDBs() {
    // Open the PDBs
	FILE *f1 = fopen("15puzzle_abs1.pdb","r");
	map1 = read_state_map(f1);
	abs1 = read_abstraction_from_file("15puzzle_abs1.abst");
	fclose(f1);

	FILE *f2 = fopen("15puzzle_abs2.pdb","r");
	map2 = read_state_map(f2);
	abs2 = read_abstraction_from_file("15puzzle_abs2.abst");
	fclose(f2);

	FILE *f3 = fopen("15puzzle_abs3.pdb","r");
	map3 = read_state_map(f3);
	abs3 = read_abstraction_from_file("15puzzle_abs3.abst");
	fclose(f3);
}

/**
 * Computes the heuristic value of a state
 * Additive PDBs
 * @param state The state to compute the heuristic value
 * @return The heuristic value of the state
 */
unsigned heuristic(state_t state) {
    // PDB values
	abstract_state(abs1, &state, &state1);
	abstract_state(abs2, &state, &state2);
	abstract_state(abs3, &state, &state3);
    
    // Sum of PDB values
    unsigned sum = *state_map_get(map1, &state1) + *state_map_get(map2, &state2) + *state_map_get(map3, &state3);
    return sum;
}