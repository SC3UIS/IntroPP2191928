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

