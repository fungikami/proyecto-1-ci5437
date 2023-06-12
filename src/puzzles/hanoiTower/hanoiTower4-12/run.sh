make hanoiTower4-12/abs1.pdb
make hanoiTower4-12/abs2.pdb

echo "A* HanoiTower4-12 (Additive PDBs)"
make hanoiTower4-12.a_star
./hanoiTower4-12.a_star < testshanoiTower4-12

echo "IDA* HanoiTower4-12 (Additive PDBs)"
make hanoiTower4-12.ida_star
./hanoiTower4-12.ida_star < testshanoiTower4-12