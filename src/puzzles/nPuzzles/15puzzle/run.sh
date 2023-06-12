# make 15puzzle/abs1.pdb
# make 15puzzle/abs2.pdb
# make 15puzzle/abs3.pdb

echo "A* 15-puzzle (Manhattan Distance)"
make 15puzzle.a_starM
./15puzzle.a_starM < tests15puzzle

echo "A* 15-puzzle (Additive PDBs)"
make 15puzzle.a_star
./15puzzle.a_star < tests15puzzle

echo "IDA* 15-puzzle (Additive PDBs)"
make 15puzzle.ida_star
./15puzzle.ida_star < tests15puzzle