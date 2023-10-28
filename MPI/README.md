# MPI - Ecuación del Calor

Este programa en lenguaje C aborda la solución de la Ecuación del Calor en un dominio bidimensional mediante el modelo de programación paralela MPI (Interface de Paso de Mensajes). La Ecuación del Calor se emplea para simular la propagación de la temperatura en una placa bidimensional a lo largo del tiempo.

## Código Principal

El código proporcionado resuelve la Ecuación de Calor en 2D mediante el modelo de programación paralela MPI (Interface de Paso de Mensajes). A continuación, se detalla en lenguaje simple lo que realiza el código paso a paso:

## Explicación del Código (main.c)

El código proporcionado resuelve la Ecuación de Calor en 2D utilizando el modelo de programación paralela MPI (Message Passing Interface). A continuación, se explica en lenguaje sencillo lo que hace el código paso a paso:

| Paso | Descripción |
|-----|------------|
| 1. | **Inicialización y Declaración de Variables**:<br>Se definen diversas variables, como la constante de difusión `a`, dos campos `current` y `previous` que indican la temperatura actual y previa, y otras variables para controlar el tiempo y la paralelización. |
| 2. | **Inicialización de MPI**:<br>Se inicia MPI (Message Passing Interface) para habilitar la comunicación y coordinación entre múltiples procesos que trabajan en paralelo. |
| 3. | **Inicialización de Campos y Parámetros**:<br>Se inicializan los campos de temperatura `current` y `previous` y se establece el número de pasos de tiempo `nsteps` y otros parámetros relevantes. También se inicializa información sobre la paralelización. |
| 4. | **Salida Inicial**:<br>Se genera una salida que representa el campo de temperatura inicial y se escribe en un archivo. |
| 5. | **Cálculo del Paso de Tiempo**:<br>Se calcula el tamaño del paso de tiempo `dt` basado en las dimensiones de la malla y la constante de difusión `a`. Esto asegura que el proceso sea estable. |
| 6. | **Evolución Temporal**:<br>Se inicia un bucle que ejecuta la evolución de la temperatura a lo largo del tiempo. Durante cada iteración, se realiza una serie de pasos, incluyendo operaciones de intercambio de información, evolución del interior del dominio, actualización de la temperatura, operaciones de intercambio para sincronizar información, evolución del borde del dominio, guardar el campo de temperatura en archivos de imagen, guardar un "checkpoint" del estado actual y el intercambio de campos `current` y `previous`. |
| 7. | **Medición del Tiempo**:<br>Se mide el tiempo que ha tardado la iteración de la simulación. |
| 8. | **Salida de Resultados Finales**:<br>Se imprime el tiempo que tomó la simulación y se muestra un valor de referencia en la posición (5, 5) del campo de temperatura final. |
| 9. | **Finalización y Limpieza**:<br>Se escribe el campo de temperatura final en un archivo y se realiza una limpieza de recursos. MPI se cierra con `MPI_Finalize()`. |


## Estructura del solución

El conjunto de códigos se compone de varios archivos fuente, cada uno con una función específica:

- `core.c`:  Implementa la lógica central para resolver la Ecuación del Calor.
- `heat.h`: Archivo de cabecera que define estructuras y prototipos de funciones.
- `io.c`: Contiene funciones para leer y escribir datos.
- `main.c`: El programa principal que configura y dirige la ejecución.
- `pngwriter.c` y `pngwriter.h`: Ofrecen funciones para guardar los resultados en archivos PNG.
- `setup.c`: Contiene funciones para la inicialización del programa.
- `utilities.c`: Funciones auxiliares para gestionar los campos de temperatura y matrices.

## Instrucciones de Compilación

A continuación se describen los pasos necesarios para compilar el código proporcionado en el archivo `main.c`. 


### 1. Ingresar al Entorno de MPI

Para comenzar, es necesario acceder a un entorno que sea compatible con MPI. En general, esto involucra el uso de comandos como `srun` para iniciar procesos MPI. Como ejemplo, puedes iniciar un entorno con 24 procesos de la siguiente manera:

```bash
srun -n X --pty /bin/bash
```	

Siendo `X` el numero de hilos a utilizar del cluster de GUANE

### 2. Cargar los Módulos Necesarios

Luego, debemos cargar los módulos necesarios, o sea, el módulo OpenMPI:

```bash
module load devtools/mpi/openmpi/3.1.4
```

### 3. Limpieza y Compilación

Para compilar el programa, podemos utilizar el archivo Makefile que se proporciona. Pero debemos eliminar archivos temporales generados previamente, para eso ejecutamos un make clean:

```bash
make clean
```

Luego de la limpieza, procede a compilar el código utilizando el siguiente comando:

```bash
make
```

Alternativamente, si preferimos compilar el programa sin utilizar el archivo `Makefile`, podemos hacerlo directamente empleando el comando `mpicc` de la siguiente manera:

```bash
mpicc -O3 -Wall -o heat_mpi main.c core.c setup.c utilities.c io.c pngwriter.c -lpng -lm
```

Podemos utilizar las flags que deseemos para diferentes niveles de optimización, como: `-O1`, `-O2`, `-O3`, `-Ofast`, `-Og`, etc.

Este comando compilará todos los archivos fuente y generará un ejecutable denominado `heat_mpi`. Los argumentos `-O3` y `-Wall` habilitan optimizaciones y muestran advertencias, respectivamente. Las opciones `-lpng` y `-lm` se utilizan para enlazar las bibliotecas necesarias.

## Ejecución Interactiva

Podemos ejecutar el programa interactivamente utilizando el comando `mpirun`. A continuación se describen varias opciones para ejecutar el programa con diferentes condiciones iniciales y parámetros de tiempo. Asegúrate de haber compilado el programa siguiendo las instrucciones previamente proporcionadas.

### 1. Valores Predeterminados

Para ejecutar el programa con los valores predeterminados, utiliza el siguiente comando:

```bash
mpirun -np 8 ./heat_mpi
```

Esto ejecutará el programa con valores predeterminados para el campo inicial y los parámetros de tiempo.

### 2. Campo Inicial desde un Archivo

Puedes utilizar un archivo de entrada para definir el campo inicial de temperatura. Por ejemplo, si tienes un archivo llamado botella.dat, ejecuta el programa de la siguiente manera:

```bash
mpirun -np 8 ./heat_mpi botella.dat
```

Esto tomará el campo inicial del archivo botella.dat como punto de partida.

### 3. Campo Inicial desde un Archivo y Pasos de Tiempo

Para especificar tanto el campo inicial desde un archivo como el número de pasos de tiempo, utilizamos el siguiente formato:

```bash
mpirun -np 8 ./heat_mpi botella.dat 1000
```

Esto cargará el campo inicial desde botella.dat y realizará 1000 pasos de tiempo.

### 4. Dimensiones y Pasos de Tiempo Personalizados

Para definir dimensiones personalizadas (ancho y alto) y el número de pasos de tiempo, podemos hacerlo de la siguiente manera:

```bash
mpirun -np 8 ./heat_mpi [ANCHO] [ALTO] [PASOS]
```

Por ejemplo:

```bash
mpirun -np 8 ./heat_mpi 800 800 1000
```

Todos estos comandos, generarán una serie de archivos heat_NUM_figura.png que representan el desarrollo temporal del campo de temperatura. Podemos utilizar cualquier visor de gráficos para visualizar estos resultados.

## Ejecución Pasiva

Para ejecutar el programa en modo pasivo utilizando sbatch y garantizar que se cargue el módulo MPI recomendado antes de la ejecución, debemos seguir estos pasos:

### 1. Crear un archivo de script de trabajo

Crear un archivo de script de trabajo, por ejemplo, run_heat_mpi.sh, utilizando un editor de texto. Similar al siguiente contenido en el archivo:
```bash
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
```

### 2. Enviar el trabajo a Slurm

Utilizando el comando sbatch para enviar el trabajo a Slurm. El script se someterá y ejecutará según las opciones especificadas en el script de trabajo. Asegúrate de estar en el directorio donde se encuentra el script:

```bash 
sbatch run_heat_mpi.sh
```


## Pruebas de Rendimiento - Solución de la Ecuación del Calor con MPI

Se presentan los resultados de pruebas de rendimiento realizadas en la solución de la Ecuación del Calor con MPI sin ninguna mejora solo utilizando las banderas `-O3 -Wall`.  Se comparan los tiempos de ejecución entre la versión original del código y la versión paralelizada para evaluar el impacto de la paralelización en el rendimiento.


  
Se realizaron tres pruebas de rendimiento utilizando diferentes configuraciones de entrada:

1. **Prueba 1:** Se utilizó el comando `mpirun -np 8 ./heat_mpi bottle.dat` con la versión original del código.
2. **Prueba 2:** Se utilizó el comando `mpirun -np 8 ./heat_mpi bottle.dat 800` con la versión original del código.
3. **Prueba 3:** Se utilizó el comando `mpirun -np 8 ./heat_mpi 600 600 1000` con la versión original del código.

Además, se realizaron las mismas tres pruebas con la versión paralelizada del código, que se titulan "Con el main.c paralelizado."

## Resultados

A continuación se presentan los resultados de las pruebas de rendimiento:

### Versión Original del Código

1. **Prueba 1:** Iteration took 63.371 seconds
   ![Texto alternativo](https://github.com/SC3UIS/IntroPP2191928/blob/main/MPI/imagenes/sinmejora1.png)

2. **Prueba 2:** Iteration took 124.787 seconds
   ![Texto alternativo](https://github.com/SC3UIS/IntroPP2191928/blob/main/MPI/imagenes/sinmejora2.png)

3. **Prueba 3:** Iteration took 156.675 seconds
   ![Texto alternativo](https://github.com/SC3UIS/IntroPP2191928/blob/main/MPI/imagenes/sinmejora3.png)


### Versión Paralelizada del Código

1. **Prueba 1:** Iteration took 63.390 seconds
![Texto alternativo](https://github.com/SC3UIS/IntroPP2191928/blob/main/MPI/imagenes/conmejora1.png)

2. **Prueba 2:** Iteration took 125.269 seconds
![Texto alternativo](https://github.com/SC3UIS/IntroPP2191928/blob/main/MPI/imagenes/conmejora2.png)

3. **Prueba 3:** Iteration took 156.134 seconds
![Texto alternativo](https://github.com/SC3UIS/IntroPP2191928/blob/main/MPI/imagenes/conmejora3.png)


## Mejoras en el código

- Inclusión de MPI: Se agregaron llamadas a las funciones MPI para inicializar MPI (MPI_Init), finalizar MPI (MPI_Finalize), obtener el rango del proceso actual (parallelization.rank), y más. Estas llamadas permiten la comunicación y la sincronización entre los procesos paralelos.

- División del Dominio: Se dividió el dominio en una malla 2D, y cada proceso es responsable de calcular una parte de la malla. Esto permite que varios procesos trabajen en paralelo en secciones separadas del problema.

- Funciones de Intercambio de Información: Se agregaron funciones para inicializar (exchange_init) y finalizar (exchange_finalize) el intercambio de información entre procesos. Estas funciones aseguran que los valores en los bordes de las submallas se actualicen correctamente.

- Cálculo Paralelo: La evolución de la temperatura se realiza en paralelo en cada proceso, lo que permite que varios procesos trabajen simultáneamente en diferentes partes del dominio.

- Sincronización Eficiente: Se gestionó la sincronización de los procesos de manera eficiente utilizando MPI, lo que garantiza que los procesos se comuniquen y cooperen adecuadamente en la simulación.

- Distribución de Trabajo: La carga de trabajo se distribuyó entre múltiples procesos para acelerar el cálculo de la Ecuación del Calor en 2D.

- Uso de la Marca de Tiempo MPI: Se utilizó MPI_Wtime para medir el tiempo de CPU utilizado para la iteración, lo que permite conocer el rendimiento de la simulación.

## Conclusiones

Basándonos en los resultados de las pruebas de rendimiento, podemos sacar las siguientes conclusiones:

1. En la "Prueba 1", la versión paralelizada del código logró un rendimiento similar a la versión original. Esto sugiere que la paralelización puede ser beneficiosa en ciertos escenarios, pero no necesariamente mejora el rendimiento en todos los casos.

2. En la "Prueba 2", la versión paralelizada tomó más tiempo en comparación con la versión original. Esto podría deberse a la sobrecarga adicional de la paralelización en configuraciones más pequeñas.

3. En la "Prueba 3", ambas versiones del código tuvieron un rendimiento similar. Esto indica que la paralelización no siempre es la solución óptima y que el rendimiento puede depender de varios factores, incluido el tamaño del problema.




