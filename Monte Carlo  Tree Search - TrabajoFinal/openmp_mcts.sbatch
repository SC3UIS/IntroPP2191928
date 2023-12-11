#!/bin/bash
#SBATCH --job-name=MPI
#SBATCH --nodes=2
#SBATCH --ntasks=2 
#SBATCH --cpus-per-task=8

#SBATCH --output=output_MCTS.txt%j.out
#SBATCH --error=error_MCTS.err%j.err 

## Se compilan los archivos "MCTS_OpenMP.c"
gcc -fopenmp MCTS_OpenMP.c -o MCTS_OpenMP