#!/bin/bash
#SBATCH --ntasks=1                    # Número total de tarefas MPI a serem lançadas
#SBATCH --nodes=1                     # Número de nós requeridos
#SBATCH --partition=express 
#SBATCH --mem=500M
#SBATCH --cpus-per-task=8

./3_pi_Nthreads_funcao