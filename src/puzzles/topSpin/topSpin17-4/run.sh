make topSpin17-4/abs1.pdb
make topSpin17-4/abs2.pdb
make topSpin17-4/abs3.pdb

echo "A* Top Spin 17-4 (Additive PDBs)"
make topSpin17-4.a_star
./topSpin17-4.a_star < teststopSpin17-4

echo "IDA* Top Spin 17-4 (Additive PDBs)"
make topSpin17-4.ida_star
./topSpin17-4.ida_star < teststopSpin17-4