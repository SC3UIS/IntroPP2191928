#!/bin/bash
#SBATCH --job-name=SumPar_Fibonacci
#SBATCH --output=output_sumfibo_omp.txt    
#SBATCH --ntasks=1    
#SBATCH --nodes=1   
#SBATCH --cpus-per-task=4    

gcc -Wall -fopenmp -std=c99 sumfibonacci_omp.c -o sumfibo_omp   
./omp_trapecio    
