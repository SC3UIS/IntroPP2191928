# Primer Taller - OpenMP (Fibonacci)
 
En esta carpeta se encuentran los archivos relacionados con la solución secuencial y paralela del problema de suma de números de Fibonacci utilizando OpenMP.

## Contenido de la Carpeta

- `sumfibonacci.c`: Código fuente de la solución secuencial en C para calcular la suma de números de Fibonacci en índices pares.
- `sumfibonacci_omp.c`: Código fuente de la solución paralela en C utilizando OpenMP para calcular la suma de números de Fibonacci en índices pares.
- `sumfibo`: Ejecutable generado a partir de `sumfibonacci.c`.
- `sumfibo_omp`: Ejecutable generado a partir de `sumfibonacci_omp.c`.

## Descripción del Problema

En matemáticas, la sucesión de Fibonacci es una secuencia infinita de números naturales. Cada término de la secuencia es la suma de los dos términos anteriores. Para este ejemplo, se ha implementado un programa en C para encontrar la suma de números de Fibonacci en índices pares hasta un valor N. Esto se hace tanto de manera secuencial como paralela utilizando OpenMP.

## Instrucciones de Compilación y Ejecución

### Descarga de archivos

Para obtener los archivos de este repositorio en el servidor GUANE o localmente, se puede utilizar las siguientes opciones:

- Utiliza `wget` para descargar los archivos:
```wget https://github.com/Kevin-STU/IntroPP2191928.git```

- O clona el repositorio utilizando `git`:
```git clone https://github.com/Kevin-STU/IntroPP2191928.git```

### Compilación y Ejecución

Para compilar el código secuencial, se utiliza el siguiente comando:

```gcc -Wall -fopenmp -std=c99 sumfibonacci.c -o sumfibo```

Donde:
- `-Wall`: Habilita todas las advertencias para una compilación más segura.
- `-fopenmp`: Habilita la biblioteca OpenMP para la programación paralela.
- `-std=c99`: Indica el estándar C99.
- `sumfibonacci.c`: El código fuente a compilar.
- `-o sumfibo`: El nombre del archivo ejecutable resultante.

Para ejecutar el programa secuencial, se usa el siguiente comando:

```./sumfibo```

Para compilar el código paralelo, se utiliza el siguiente comando:

```gcc -Wall -fopenmp -std=c99 sumfibonacci_omp.c -o sumfibo_omp```

Para ejecutar el programa paralelo, se usa el siguiente comando:
```./sumfibo_omp```

## Comparación de Tiempos de Ejecución

Se realizaron comparaciones de tiempos de ejecución con diferentes valores de N para evaluar el rendimiento de las implementaciones secuencial y paralela.

### Resultados

A continuación se presentan los tiempos de ejecución obtenidos:

- Con N = 150000:
  - Código secuencial: 3.535937 [ms]
  - ![Ejemplo](Imagenes/150000%20secuencial.png)
  - Código paralelizado: 3.192182 [ms]
  - ![Ejemplo](Imagenes/150000%20paralelizado.png)

- Con N = 5:
  - Código secuencial: 0.002108 [ms]
  - ![Ejemplo](Imagenes/5%20secuencial.png)
  - Código paralelizado: 0.431494 [ms]
  - ![Ejemplo](Imagenes/5%20paralelizado.png)

### Conclusiones

Los resultados muestran que el código paralelizado es más rápido que el código secuencial cuando se trabaja con un valor grande de N (150000 en este caso). Esto se debe a la capacidad del código paralelo para aprovechar múltiples núcleos de CPU y distribuir el trabajo de manera eficiente en problemas más grandes.

Sin embargo, es importante destacar que el código paralelizado puede mostrar un rendimiento inferior al código secuencial cuando se trabaja con valores muy pequeños de N (5 en este caso). Esto se debe a la sobrecarga introducida por la paralelización, que puede ser significativa en problemas pequeños. La administración de hilos y la sincronización entre ellos pueden requerir más tiempo que la propia ejecución secuencial del problema.

### Análisis de Complejidad

Para tener una mayor fácilidad a la hora del análisis de complejidad vamos a dividir las partes del código para entender comprender mejor la complejidad,

- Generación de la secuencia de Fibonacci: El primer bucle for calcula los números de Fibonacci hasta 2n, lo que implica un tiempo de ejecución de ```O(2n)```.

- Cálculo de la suma de números pares de Fibonacci: El segundo bucle for recorre la mitad de los elementos generados en el primer bucle, es decir, n elementos. Por lo tanto, la complejidad de este bucle es ```O(n)```.

La complejidad total del código es la suma de las complejidades de estas dos partes, lo que da como resultado ```O(2n) + O(n) = O(3n)```. 
Omitiendo las constantes multiplicativas, la complejidad final se simplifica a ```O(n)```. O sea, que la complejidad del código es lineal en función del valor de n. A medida que n crece, el tiempo de ejecución aumentará de manera proporcional.


