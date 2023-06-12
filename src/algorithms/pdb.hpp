#ifndef PDB_HPP
#define PDB_HPP

#include <climits>
#include <string>
#include <vector>

using namespace std;

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
     * @param name The name of the PDB files
     */
    PDB(string name) {
        // Load the abstraction
        abst = read_abstraction_from_file((name + ".abst").c_str());
        if (abst == NULL) {
            fprintf(stderr, "Error: invalid abstraction file.\n");
            return;
        }

        // Load the pattern database
        FILE* file = fopen((name + ".pdb").c_str(), "r");
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
     * Computes the heuristic value of a state
     * 
     * @param state The state to compute the heuristic value
     * @return The heuristic value of the state
     */
    int get_cost(state_t* state) {
        // Look for the state in the PDB
        state_t *aux_state = new state_t;
        abstract_state(abst, state, aux_state);
        int *h = state_map_get(map, aux_state);

        // If the state is not in the PDB, return infinity
        return h == NULL ? INT_MAX : *h;
    }
};

#endif
