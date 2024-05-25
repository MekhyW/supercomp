#!/bin/bash
#SBATCH --partition=espec
#SBATCH --nodes=4
#SBATCH --cpus-per-task=5
#SBATCH --mem=1GB

mpirun ./q2
