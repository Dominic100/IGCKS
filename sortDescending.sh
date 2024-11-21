#!/bin/bash

sort_descending() {
	local arr=("$@")
	local n=${#arr[@]}
	
	for ((i = 0; i < n; i++)); do
		for ((j = i + 1; j < n; j++)); do
			if ((arr[i] < arr[j])); then
				temp=${arr[i]}
				arr[i]=${arr[j]}
				arr[j]=$temp
			fi
		done
	done
	
	echo "${arr[@]}"
}

read -p "Enter array elements separated by space: " -a array

sorted_array=($(sort_descending "${array[@]}"))

echo "Sorted array in descending order: ${sorted_array[@]}"
