#include <bits/stdc++.h>

using namespace std;

void writeMove(int from, int to, fstream &file, int nTiles) {
    // LHS
    for (int i = 0; i < nTiles; i++) {
        if (i == from) file << "b ";
        else if (i == to) file << "X ";
        else file << "- ";
    }

    file << "=> ";

    // RHS
    for (int i = 0; i < nTiles; i++) {
        if (i == from) file << "X ";
        else if (i == to) file << "b ";
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
    file << "\nGOAL b ";
    for (int i = 1; i < nTiles; i++) file << i << " ";
    file << "\n";

    file.close();
}

int main (int argc, char *argv[]) {
    int n = atoi(argv[1]);
    generateNPuzzle(n);
    return 1;
}