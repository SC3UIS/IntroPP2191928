#include <stdio.h>
#include "omp.h"

/* Se utiliza unsigned long long para el 
tipo de datos debido a la necesidad de manejar 
n�meros grandes sin signo en este c�digo. */
unsigned long long calculateEvenSum(int n)
{
    // Se utiliza 2n+1 en el tama�o del arreglo fibo[] porque necesitamos 
    // almacenar los n�meros de Fibonacci desde 0 hasta 2n, lo que suma un total de 2n+1 n�meros.
    unsigned long long sum=0, fibo[2*n + 1]; 
    fibo[0]=0, fibo[1]=1;

    // Se calculan los n�meros de Fibonacci hasta 2*n
    for(int i=2; i <= 2*n; i++)
    {
        fibo[i] = fibo[i-1] + fibo[i-2];
    }
    
    // Se calcula la suma de los n�meros de Fibonacci en �ndices pares
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

    printf("\n n = %d \n Suma = %llu \n Tiempo = %f [ms]\n\n", n, sum, time);

    return 0;
}