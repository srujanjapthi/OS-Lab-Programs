#!/bin/bash

read -p "Enter a number: " num

rev=0
temp=$num

while ((temp != 0)); do
    rev=$((rev*10+temp%10))
    temp=$((temp/10))
done

if ((rev == num)); then
    echo "Number is a Palindrome."
else
    echo "Number is not a Palindrome."
fi
