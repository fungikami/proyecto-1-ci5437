#include <bits/stdc++.h>

using namespace std;

void writeMove(int from, int to, fstream &file, int nTiles) {
    // LHS
    for (int i = 0; i < nTiles; i++) {
        if (i == from) file << "0 ";
        else if (i == to) file << "X ";
        else file << "- ";
    }

    file << "=> ";

    // RHS
    for (int i = 0; i < nTiles; i++) {
        if (i == from) file << "X ";
        else if (i == to) file << "0 ";
        else file << "- ";
    }

    file << "LABEL FROM_" << from << "_TO_" << to << "\n";
}

void generateNPuzzle(int n) {
    int nTiles = n + 1;
    int nTilesRow = sqrt(nTiles);

    fstream file;
    ostringstream os;
    os << n << "-puzzle.psvn";
    string s = os.str();

    // Create file 
    file.open(s, ios::out);
    if (!file) {
        cout<<"Error creating file"<<endl;
        return;
    }

    // Header
    file << "# Ka Fung & Christopher Gómez\n";
    file << "# " << n << "-puzzle\n\n";
    file << "# There are " << nTiles << " tiles\n";
    file << nTiles << "\n\n";
    file << "# Every space has " << nTiles << " possible values\n";
    for (int i = 0; i < nTiles; i++) file << nTiles << " ";

    file << "\n\n";

    // Executes clockwise movements starting from the top left corner
    for (int i = 0; i < nTiles; i++) {
        // Move up
        if (i >= nTilesRow) writeMove(i, i-nTilesRow, file, nTiles);

        // Move right
        if (i % nTilesRow != (nTilesRow - 1)) writeMove(i, i+1, file, nTiles);

        // Move down
        if (i < nTiles - nTilesRow) writeMove(i, i+nTilesRow, file, nTiles);

        // Move left
        if (i % nTilesRow != 0) writeMove(i, i-1, file, nTiles);
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
