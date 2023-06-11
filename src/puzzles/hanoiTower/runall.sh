#!/usr/bin/bash

if [ -z "$1" ]
then
    echo "Usage: ./runall.sh <name>"
    exit 1
fi

mkdir results

echo "Running IDDFS Hanoi Tower 4-12, 15 minutes without pruning"
timeout 900 ./hanoiTower4-12.iddfs > "results/${1}_iddfs_hanoiTower4-12_nopruning.md" &

echo "Running IDDFS Hanoi Tower 4-12, 15 minutes with pruning"
timeout 900 ./hanoiTower4-12.iddfs p > "results/${1}_iddfs_hanoiTower4-12_pruning.md" &

echo "Running IDDFS Hanoi Tower 4-14, 15 minutes without pruning"
timeout 900 ./hanoiTower4-14.iddfs > "results/${1}_iddfs_hanoiTower4-14_nopruning.md" &

echo "Running IDDFS Hanoi Tower 4-14, 15 minutes with pruning"
timeout 900 ./hanoiTower4-14.iddfs p > "results/${1}_iddfs_hanoiTower4-14_pruning.md" &

echo "Running IDDFS Hanoi Tower 4-18, 15 minutes without pruning"
timeout 900 ./hanoiTower4-18.iddfs > "results/${1}_iddfs_hanoiTower4-18_nopruning.md" &

echo "Running IDDFS Hanoi Tower 4-18, 15 minutes with pruning"
timeout 900 ./hanoiTower4-18.iddfs p > "results/${1}_iddfs_hanoiTower4-18_pruning.md" &