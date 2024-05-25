#!/bin/bash
#SBATCH --partition=espec
#SBATCH --nodes=1
#SBATCH --cpus-per-task=2
#SBATCH --mem=1GB
#SBATCH --output=1000_2_cores.out

./matrix_1000