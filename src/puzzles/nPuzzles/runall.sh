#!/usr/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./runall.sh <name>"
    exit 1
fi

mkdir results

echo "Running IDDFS 15-puzzle, 15 minutes without pruning"
timeout 900 ./15puzzle.iddfs > "results/${1}_iddfs_15min_nopruning.md" &

echo "Running IDDFS 15-puzzle, 15 minutes with pruning"
timeout 900 ./15puzzle.iddfs p > "results/${1}_iddfs_15min_pruning.md" &

echo "Running IDDFS 24-puzzle, 15 minutes without pruning"
timeout 900 ./24puzzle.iddfs > "results/${1}_iddfs_24min_nopruning.md" &

echo "Running IDDFS 24-puzzle, 15 minutes with pruning"
timeout 900 ./24puzzle.iddfs p > "results/${1}_iddfs_24min_pruning.md" &