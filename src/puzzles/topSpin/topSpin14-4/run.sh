make topSpin14-4/abs1.pdb
make topSpin14-4/abs2.pdb
make topSpin14-4/abs3.pdb

echo "A* Top Spin 14-4 (Additive PDBs)"
make topSpin14-4.a_star
./topSpin14-4.a_star < teststopSpin14-4

echo "IDA* Top Spin 14-4 (Additive PDBs)"
make topSpin14-4.ida_star
./topSpin14-4.ida_star < teststopSpin14-4