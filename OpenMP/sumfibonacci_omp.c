#include <stdio.h>
#include "omp.h"

unsigned long long calculateEvenSum(int n)
{
    unsigned long long sum=0, fibo[2*n + 1];
    fibo[0]=0, fibo[1]=1;

    for(int i=2; i <= 2*n; i++)
    {
        fibo[i] = fibo[i-1] + fibo[i-2];
    }
    
    // Los cálculos a continuación se realizarán 
    // en paralelo por múltiples hilos.
    
    // Además, se añade la directiva "reduction(+:sum)" para asegurar que las
    // sumas parciales realizadas por cada hilo se agreguen correctamente a "sum".
    #pragma omp parallel for reduction(+:sum)
    for(int i=0; i <= 2*n; i+=2)
    {
        sum+=fibo[i];
    }

    return sum;
}

int main()
{
    int n = 150000;

    double start = omp_get_wtime();
    unsigned long long sum = calculateEvenSum(n);
    double final = omp_get_wtime();


    double time = (final-start)*1000;

    printf("\n n = %d \n Suma paralelizada = %llu \n Tiempo = %f [ms]\n\n", n, sum, time);

    return 0;
}