# make 24puzzle/abs1.pdb
# make 24puzzle/abs2.pdb
# make 24puzzle/abs3.pdb
# make 24puzzle/abs4.pdb
# make 24puzzle/abs5.pdb

echo "A* 24-puzzle (Additive PDBs)"
make 24puzzle.a_star
./24puzzle.a_star < tests24puzzle

echo "IDA* 24-puzzle (Additive PDBs)"
make 24puzzle.ida_star
./24puzzle.ida_star < tests24puzzle