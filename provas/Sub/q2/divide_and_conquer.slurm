#!/bin/bash
#SBATCH --job-name=divide_and_conquer
#SBATCH --output=divide_and_conquer.out
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=8
#SBATCH --partition=espec
#SBATCH --mem=500mb

g++ -fopenmp -o divide_and_conquer divide_and_conquer.cpp
./divide_and_conquer
