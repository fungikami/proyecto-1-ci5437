make hanoiTower4-18/abs1.pdb
make hanoiTower4-18/abs2.pdb
make hanoiTower4-18/abs3.pdb

echo "A* HanoiTower4-18 (Additive PDBs)"
make hanoiTower4-18.a_star
./hanoiTower4-18.a_star < testshanoiTower4-18

echo "IDA* HanoiTower4-18 (Additive PDBs)"
make hanoiTower4-18.ida_star
./hanoiTower4-18.ida_star < testshanoiTower4-18