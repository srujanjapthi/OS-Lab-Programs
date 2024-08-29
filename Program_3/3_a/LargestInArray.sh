#!/bin/bash

read -p "Enter the number of Elements: " n

echo -n "Enter $n elements: "
for ((i = 0; i < n; i++)); do
    read numbers[$i]
done

largest=${numbers[0]}

for num in ${numbers[@]}; do
    if ((num > largest)); then
        largest=$num
    fi
done

echo "The largest number is: $largest"
