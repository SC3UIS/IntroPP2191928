#!/bin/bash
#SBATCH --job-name=heat_mpi_job   # Nombre del trabajo
#SBATCH --ntasks=8               # Número total de tareas MPI
#SBATCH --nodes=2                # Número de nodos
#SBATCH --cpus-per-task=1        # Número de hilos de CPU por tarea
#SBATCH --output=heat_mpi_output.txt

# Carga del módulo MPI recomendado
module load devtools/mpi/openmpi/3.1.4

# Ruta al ejecutable y argumentos
EXECUTABLE=./heat_mpi
INPUT_FILE=botella.dat
NUM_STEPS=1000

# Ejecución del programa con MPI
mpirun -np ./heat_mpi