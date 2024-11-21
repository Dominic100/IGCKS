#!/bin/bash

sum_of_digits() {
	local num=$1
	local sum=0

	while [ $num -gt 0 ]; do
		digit=$((num % 10))
		sum=$((sum + digit))
		num=$((num / 10))
	done

	echo $sum
}

read -p "Enter a number: " number

if [[ ! $number =~ ^[0-9]+$ ]]; then
	echo "Please enter a valid positive integer."
	exit 1
fi

result=$(sum_of_digits $number)
echo "The sum of digits of $number is: $result"
