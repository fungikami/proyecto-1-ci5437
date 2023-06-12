make hanoiTower4-14/abs1.pdb
make hanoiTower4-14/abs2.pdb

echo "A* HanoiTower4-14 (Additive PDBs)"
make hanoiTower4-14.a_star
./hanoiTower4-14.a_star < testshanoiTower4-14

echo "IDA* HanoiTower4-14 (Additive PDBs)"
make hanoiTower4-14.ida_star
./hanoiTower4-14.ida_star < testshanoiTower4-14