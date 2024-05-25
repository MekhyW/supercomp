#!/bin/bash
#SBATCH --partition=espec
#SBATCH --nodes=1
#SBATCH --cpus-per-task=4
#SBATCH --mem=1GB
#SBATCH --output=10000_4_cores.out

./matrix_1000