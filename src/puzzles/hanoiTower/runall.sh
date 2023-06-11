#!/usr/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./runall.sh <name>"
    exit 1
fi

mkdir results

echo "Running IDDFS Hanoi Tower 4-12, 15 minutes without pruning"
taskset -c 1 timeout 900 ./hanoiTower4-12.iddfs > "results/${1}_iddfs_hanoiTower4-12_nopruning.csv" &

echo "Running IDDFS Hanoi Tower 4-12, 15 minutes with pruning"
taskset -c 2 timeout 900 ./hanoiTower4-12.iddfs p > "results/${1}_iddfs_hanoiTower4-12_pruning.csv" &

echo "Running IDDFS Hanoi Tower 4-14, 15 minutes without pruning"
taskset -c 3 timeout 900 ./hanoiTower4-14.iddfs > "results/${1}_iddfs_hanoiTower4-14_nopruning.csv" &

echo "Running IDDFS Hanoi Tower 4-14, 15 minutes with pruning"
taskset -c 4 timeout 900 ./hanoiTower4-14.iddfs p > "results/${1}_iddfs_hanoiTower4-14_pruning.csv" &

echo "Running IDDFS Hanoi Tower 4-18, 15 minutes without pruning"
taskset -c 5 timeout 900 ./hanoiTower4-18.iddfs > "results/${1}_iddfs_hanoiTower4-18_nopruning.csv" &

echo "Running IDDFS Hanoi Tower 4-18, 15 minutes with pruning"
taskset -c 6 timeout 900 ./hanoiTower4-18.iddfs p > "results/${1}_iddfs_hanoiTower4-18_pruning.csv" &