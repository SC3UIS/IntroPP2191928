#!/bin/bash
#SBATCH --job-name=heat_mpi_job   # Nombre del trabajo
#SBATCH --ntasks=8               # N�mero total de tareas MPI
#SBATCH --nodes=2                # N�mero de nodos
#SBATCH --cpus-per-task=1        # N�mero de hilos de CPU por tarea
#SBATCH --output=heat_mpi_output.txt

# Carga del m�dulo MPI recomendado
module load devtools/mpi/openmpi/3.1.4

# Ruta al ejecutable y argumentos
EXECUTABLE=./heat_mpi
INPUT_FILE=botella.dat
NUM_STEPS=1000

# Ejecuci�n del programa con MPI
mpirun -np ./heat_mpi