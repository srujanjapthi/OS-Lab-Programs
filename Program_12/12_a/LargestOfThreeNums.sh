#!/bin/bash

# Write a shell program to find the largest of three numbers

read -p "Enter three numbers: " num1 num2 num3

echo -n "Largest Number is: "
if ((num1 > num2 && num1 > num3)); then
    echo $((num1))
elif ((num2 > num3)); then
    echo $((num2))
else
    echo $((num3))
fi
