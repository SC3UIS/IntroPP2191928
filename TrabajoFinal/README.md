# Trabajo Final - Optimización de Monte Carlo Tree Search (MCTS) con OpenMP

Este repositorio aborda el objetivo de paralelizar y optimizar el método de Monte Carlo Tree Search (MCTS) mediante el uso de OpenMP. MCTS es comúnmente utilizado en la toma de decisiones en entornos de inteligencia artificial y juegos.

## ¿Qué es Monte Carlo Tree Search (MCTS)?

Monte Carlo Tree Search (MCTS) es un algoritmo de búsqueda basado en la simulación de juegos. Se utiliza para la toma de decisiones en situaciones donde el espacio de búsqueda es muy grande y no se puede explorar completamente. MCTS ha demostrado ser eficaz en juegos de estrategia y otras áreas de inteligencia artificial.

El proceso de MCTS se divide en varias fases:
1. **Selección:** Selecciona nodos en el árbol basándose en algún criterio.
2. **Expansión:** Expande el árbol añadiendo nuevos nodos.
3. **Simulación o Rollout:** Simula jugadas hasta llegar a un resultado.
4. **Retropropagación:** Actualiza la información del árbol basándose en el resultado de la simulación.

A continuación, se presenta la imagen de referencia que ilustra las fases del MCTS:

![MCTS phases](https://i.stack.imgur.com/wZAqy.png "MCTS phases")

## Contenido del Repositorio

### Carpeta "MonteCarloTreeSearch-NO OpenMP"

- **readme.md:** Documentación detallada sobre la implementación de Monte Carlo Tree Search en C++, incluyendo aplicaciones a Quoridor, detalles de implementación y fundamentos del MCTS (Selection, Expansion, Simulation or rollout, y Backpropagation).

- **makefile:** Archivo para compilar todos los archivos, incluyendo el código principal de MCTS y ejemplos de juegos (TicTacToe y Quoridor).

- **mcts.cpp:** Código principal que implementa el método Monte Carlo Tree Search.

- **JobScheduler.cpp:** Implementación de un planificador de trabajos para la ejecución paralela de rollouts en el MCTS.

- **Carpeta "Examples":** Contiene dos carpetas separadas para la aplicación del método MCTS en los juegos TicTacToe y Quoridor.

### Carpeta "MonteCarloTreeSearch-OpenMP"

Similar a la carpeta anterior, pero en el código principal `mcts.cpp` se ha introducido paralelismo en la función `rollout` utilizando OpenMP. Se muestra un extracto del código donde se implementa la paralelización.

```cpp
void MCTS_node::rollout() {

    #pragma omp parallel for
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
    }
}


1. **`#pragma omp parallel for`:** Esta línea indica al compilador que la siguiente estructura de bucle debe ejecutarse en paralelo. OpenMP se encargará de distribuir las iteraciones del bucle entre varios hilos de ejecución. Cada hilo ejecutará una porción del bucle de manera concurrente.

2. **`for (int i = 0; i < NUMBER_OF_THREADS; i++)`:** Este es el bucle que se ejecutará en paralelo. Cada iteración del bucle representa una tarea que puede ejecutarse de manera independiente.

3. **`// ... código paralelo ...`:** Aquí iría el código que se ejecutará de manera paralela. Cada hilo ejecutará esta sección de código para una iteración específica del bucle.

4. **`// ... más código ...`:** Cualquier código adicional después del bucle paralelo.

Este bloque de código paraleliza la ejecución de un bucle, distribuyendo las iteraciones entre múltiples hilos. Específicamente, el bucle paralelizado se utiliza para realizar tareas independientes en paralelo, aprovechando así la capacidad de procesamiento multicore de la máquina. En el contexto del MCTS, este enfoque paralelo puede acelerar el proceso de simulación o rollout, lo que contribuye a una mejora en el rendimiento general del algoritmo.

