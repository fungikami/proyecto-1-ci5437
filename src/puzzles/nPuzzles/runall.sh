#!/usr/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./runall.sh <name>"
    exit 1
fi

mkdir results

echo "Running IDDFS 15-puzzle, 15 minutes without pruning"
taskset -c 1 timeout 900 ./15puzzle.iddfs > "results/${1}_iddfs_15puzzle_nopruning.csv" &

echo "Running IDDFS 15-puzzle, 15 minutes with pruning"
taskset -c 2 timeout 900 ./15puzzle.iddfs p > "results/${1}_iddfs_15puzzle_pruning.csv" &

echo "Running IDDFS 24-puzzle, 15 minutes without pruning"
taskset -c 3 timeout 900 ./24puzzle.iddfs > "results/${1}_iddfs_24puzzle_nopruning.csv" &

echo "Running IDDFS 24-puzzle, 15 minutes with pruning"
taskset -c 4 timeout 900 ./24puzzle.iddfs p > "results/${1}_iddfs_24puzzle_pruning.csv" &