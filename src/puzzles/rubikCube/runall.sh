#!/usr/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./runall.sh <name>"
    exit 1
fi

mkdir results

echo "Running IDDFS Rubik Cube, 15 minutes without pruning"
taskset -c 1 timeout 900 ./rubik3Sticker.iddfs > "results/${1}_iddfs_rubik3Sticker_nopruning.csv" &

echo "Running IDDFS Rubik Cube, 15 minutes with pruning"
taskset -c 2 timeout 900 ./rubik3Sticker.iddfs p > "results/${1}_iddfs_rubik3Sticker_pruning.csv" &