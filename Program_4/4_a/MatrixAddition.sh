#!/bin/bash

read -p "Enter the order of the matrices: " m n

declare -A matrix1
declare -A matrix2
declare -A res

echo "Enter the elements of the matrix 1: "
for ((i = 0; i < m; i++)); do
    for ((j = 0; j < n; j++)); do
        read matrix1[$i,$j]
    done
done

echo
echo "Enter the elements of the matrix 2: "
for ((i = 0; i < m; i++)); do
    for ((j = 0; j < n; j++)); do
        read matrix2[$i,$j]
    done
done

echo
echo "Result Matrix: "
for ((i = 0; i < m; i++)); do
    for ((j = 0; j < n; j++)); do
        res[$i,$j]=$((matrix1[$i,$j]+matrix2[$i,$j]))
        echo -n "${res[$i,$j]} "
    done
    echo
done
