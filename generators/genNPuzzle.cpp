#include <bits/stdc++.h>

using namespace std;

void writeMove(int x, int y, fstream &file, int nTiles) {
    // LHS
	for (int i = 0; i < nTiles; i++) {
		if (i == x) {
			file << "b ";
		} else if (i == y) {
			file << "X ";
		} else {
			file << "- ";
		}
	}

	file << "=> ";

    // RHS
	for (int i = 0; i < nTiles; i++) {
		if (i == x) {
            file << "X ";
        } else if (i == y) {
            file << "b ";
        } else {
            file << "- ";
        }
	}

    file << "LABEL FROM_" << x << "_TO_" << y << "\n";
}

void generateNPuzzle(int n) {
    int nTiles = n + 1;
	int nTilesRow = sqrt(nTiles);

    fstream file;
    ostringstream os;
    os << "psvn/" << n << "-puzzle.psvn";
    string s = os.str();

    // Create file 
    file.open(s, ios::out);
    if(!file){
        cout<<"Error creating file"<<endl;
        return;
    }

    // Header
    file << "# " << n << "-puzzle\n\n";
    file << "DOMAIN tile " << nTiles << " \n\t\t";
    file << "b ";
	for (int i = 1; i < nTiles; i++) file << i << " ";

    file << "\n\n" << nTiles << "\n\n";

	for (int i = 0; i < nTiles; i++) file <<"tile ";
	file << "\n\n";

	for (int i = 0; i < nTiles; i++) {
        // Move to right: If not on right edge
		if (i % nTilesRow != (nTilesRow - 1)) writeMove(i, i+1, file, nTiles);

        // Move to left: If not on left edge
		if (i % nTilesRow != 0) writeMove(i, i-1, file, nTiles);

        // Move up: If not on top edge
		if (i >= nTilesRow) writeMove(i, i-nTilesRow, file, nTiles);

		// Move down: If not on bottom edge
		if (i < nTiles - nTilesRow) writeMove(i, i+nTilesRow, file, nTiles);
	}

    // Goal
	file << "\nGOAL ";
	for (int i = 0; i < nTiles; i++) file << i << " ";
	file << "\n";

    file.close();
}

int main (int argc, char *argv[]) {
	int n = atoi(argv[1]);
    generateNPuzzle(n);
	return 1;
}