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
        string abst_filename = prefix + ".abst";
        abst = read_abstraction_from_file(abst_filename.c_str());
        if (abst == NULL) {
            fprintf(stderr, "Couldn't read the abstraction %s\n", filename.c_str());
            return;
        }

        // Load the pattern database (state_map)
        string map_filename = prefix + ".state_map";
        FILE* file = fopen(map_filename.c_str(), "r");
        if (file == NULL) {
            fprintf(stderr, "Couldn't open the pdb file %s\n", map_filename.c_str());
            destroy_abstraction(abst);
            return;
        }

        map = read_state_map(file);
        fclose(file);
        if (map == NULL) {
            fprintf(stderr, "Couldn't read the pdb %s\n", map_filename.c_str());
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
