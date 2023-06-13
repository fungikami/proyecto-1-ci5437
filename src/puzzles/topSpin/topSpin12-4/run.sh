# make topSpin12-4/abs1.pdb
# make topSpin12-4/abs2.pdb
# make topSpin12-4/abs3.pdb

echo "A* Top Spin 12-4 (Additive PDBs)"
make topSpin12-4.a_star
./topSpin12-4.a_star < teststopSpin12-4

echo "IDA* Top Spin 12-4 (Additive PDBs)"
make topSpin12-4.ida_star
./topSpin12-4.ida_star < teststopSpin12-4