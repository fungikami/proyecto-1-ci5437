#!/usr/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./runall.sh <name>"
    exit 1
fi

mkdir results

echo "Running IDDFS top spin 12-4, 15 minutes without pruning"
taskset -c 1 timeout 900 ./topSpin12-4.iddfs > "results/${1}_iddfs_topSpin12-4_nopruning.csv" &

echo "Running IDDFS top spin 12-4, 15 minutes with pruning"
taskset -c 2 timeout 900 ./topSpin12-4.iddfs p > "results/${1}_iddfs_topSpin12-4_pruning.csv" &

echo "Running IDDFS top spin 14-4, 15 minutes without pruning"
taskset -c 3 timeout 900 ./topSpin14-4.iddfs > "results/${1}_iddfs_topSpin14-4_nopruning.csv" &

echo "Running IDDFS top spin 14-4, 15 minutes with pruning"
taskset -c 4 timeout 900 ./topSpin14-4.iddfs p > "results/${1}_iddfs_topSpin14-4_pruning.csv" &

echo "Running IDDFS top spin 17-4, 15 minutes without pruning"
taskset -c 5 timeout 900 ./topSpin17-4.iddfs > "results/${1}_iddfs_topSpin17-4_nopruning.csv" &

echo "Running IDDFS top spin 17-4, 15 minutes with pruning"
taskset -c 6 timeout 900 ./topSpin17-4.iddfs p > "results/${1}_iddfs_topSpin17-4_pruning.csv" &