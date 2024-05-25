#!/bin/bash
#SBATCH --partition=prova
#SBATCH --nodes=2
#SBATCH --cpus-per-task=5
#SBATCH --mem=3GB

export OMP_NUM_THREADS=10

./executavel
