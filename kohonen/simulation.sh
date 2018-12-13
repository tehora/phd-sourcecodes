#!/bin/zsh

down=$1
up=$2

for j in {$down..$up}; do
	time PARAM=$j make classify
	mv classify$j.txt simulations/classify_$j.txt
	mv neurons$j.txt simulations/neurons_$j.txt
done
