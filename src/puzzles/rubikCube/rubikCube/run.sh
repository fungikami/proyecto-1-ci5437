make rubik3Sticker/abs1.pdb
make rubik3Sticker/abs2.pdb
make rubik3Sticker/abs3.pdb

echo "A* Rubik Cube (Additive PDBs)"
make rubik3Sticker.a_star
./rubik3Sticker.a_star < testsrubik3Sticker

echo "IDA* Rubik Cube (Additive PDBs)"
make rubik3Sticker.ida_star
./rubik3Sticker.ida_star < testsrubik3Sticker