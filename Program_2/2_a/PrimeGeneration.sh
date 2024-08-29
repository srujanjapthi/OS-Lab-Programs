#!/bin/bash

read -p "Enter Low and High value: " low high

for ((n = low; n <= high; n++)); do
  isPrime=1
  for ((i = 2; i <= n / 2; i++)); do
    if ((n%i == 0)); then
      isPrime=0
      break
    fi
  done

  if ((isPrime != 0)); then
    echo -n "$n "
  fi
done

echo
