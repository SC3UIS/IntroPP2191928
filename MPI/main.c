/* 
   Heat equation solver in 2D.
   Date: 27 de octubre del 2023
   Author: Kevin Prada y Brayan Ferney
   Cambios:
   - Paralelización del código.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include "heat.h"

int main(int argc, char **argv)
{
    double a = 0.5;             // Constante de difusión
    field current, previous;    // Campos de temperatura actual y anterior

    double dt;                  // Paso de tiempo
    int nsteps;                 // Número de pasos de tiempo

    int image_interval = 500;    // Intervalo de salida de imágenes

    int restart_interval = 200;  // Intervalo de salida de puntos de control

    parallel_data parallelization; // Información de paralelización

    int iter, iter0;               // Contador de iteraciones

    double dx2, dy2;            // delta x y delta y al cuadrado

    double start_clock;        // Marca de tiempo inicial

    MPI_Init(&argc, &argv);

    initialize(argc, argv, &current, &previous, &nsteps, 
               &parallelization, &iter0);

    // Salida del campo inicial
    write_field(&current, iter0, &parallelization);
    iter0++;

    // Mayor paso de tiempo estable
    dx2 = current.dx * current.dx;
    dy2 = current.dy * current.dy;
    dt = dx2 * dy2 / (2.0 * a * (dx2 + dy2));

    // Obtener la marca de tiempo inicial
    start_clock = MPI_Wtime();

    // Evolución temporal
    for (iter = iter0; iter < iter0 + nsteps; iter++) {
        exchange_init(&previous, &parallelization);
        evolve_interior(&current, &previous, a, dt);
        exchange_finalize(&parallelization);
        evolve_edges(&current, &previous, a, dt);
        if (iter % image_interval == 0) {
            write_field(&current, iter, &parallelization);
        }
        // Escribir un punto de control de vez en cuando para facilitar la reanudación
        if (iter % restart_interval == 0) {
            write_restart(&current, &parallelization, iter);
        }
        // Intercambiar los campos actual y anterior
        swap_fields(&current, &previous);
    }

    // Determinar el tiempo de CPU utilizado para la iteración
    if (parallelization.rank == 0) {
        printf("La iteración tomó %.3f segundos.\n", (MPI_Wtime() - start_clock));
        printf("Valor de referencia en 5,5: %f\n", 
                        previous.data[idx(5, 5, current.ny + 2)]);
    }

    write_field(&current, iter, &parallelization);

    finalize(&current, &previous, &parallelization);
    MPI_Finalize();

    return 0;
}
