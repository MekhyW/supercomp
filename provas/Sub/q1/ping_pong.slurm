#!/bin/bash
#SBATCH --partition=espec
#SBATCH --ntasks=2
#SBATCH --mem=2G         
#SBATCH --job-name=ping_pong
#SBATCH --output=ping_pong.out
#SBATCH --error=ping_pong.err

mpic++ -o ping_pong ping_pong.cpp
mpirun -np 2 ./ping_pong
