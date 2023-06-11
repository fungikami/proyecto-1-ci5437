#ifndef PDB_HPP
#define PDB_HPP

/**
 * PDB class that stores the abstraction and the pattern database
 * 
 * @param abst The abstraction
 * @param map The pattern database
 */
class PDB {
  private:
    abstraction_t *abst;
    state_map_t *map;

  public:
    /**
     * Constructor that opens the PDBs and stores them in the class attributes
     * 
     * @param prefix The prefix of the PDB files
     */
    PDB(string prefix) {
        // Load the abstraction
        abst = read_abstraction_from_file((prefix + ".abst").c_str());
        if (abst == NULL) {
            fprintf(stderr, "Error: invalid abstraction file.\n");
            return;
        }

        // Load the pattern database
        FILE* file = fopen(prefix + ".pdb".c_str(), "r");
        if (file == NULL) {
            fprintf(stderr, "Error: invalid PDB file.\n");
            destroy_abstraction(abst);
            fclose(file);
            return;
        }

        map = read_state_map(file);
        fclose(file);
        if (map == NULL) {
            fprintf(stderr, "Error: invalid PDB file.\n");
            destroy_abstraction(abst);
            return;
        }
    }

    /**
     * Destructor that frees the memory of the PDBs and abstractions
     */
    ~PDB() {
        destroy_abstraction(abst);
        destroy_state_map(map);
    }

    /**
     * Computes the heuristic value of a state
     * 
     * @param state The state to compute the heuristic value
     * @return The heuristic value of the state
     */
    int get_cost(state_t* state) {
        // Look for the state in the PDB
        state_t abst_state;
        abstract_state(abst, state, &abst_state);
        int* h = state_map_get(map, &abst_state);

        // If the state is not in the PDB, return infinity
        return h == NULL ? INT_MAX : *h;
    }
};

#endif
