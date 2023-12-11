/*
  Purpose:
    Implementación en C del algoritmo de Monte Carlo Tree Search (MCTS) para valoración de opciones financieras de venta (put).
   
  Example:
    Este código utiliza MCTS para estimar el precio de una opción de venta financiera.

  Licensing:
    Este código se distribuye bajo la licencia GNU LGPL.

  Original Author:
    Manas Sharma 

  OpenMP Modification:
    30 de noviembre de 2023 por Kevin Prada y Ronald Arias, 
    Universidad Industrial de Santander 
    kevin2191928@correo.uis.edu.co, ronald2191927@correo.uis.edu.co
    Esta modificación OpenMP realiza una paralelización del código original.

  Description:
    El código implementa el algoritmo MCTS para valorar opciones financieras de venta utilizando el modelo Black-Scholes.
    Sin la utilización de OpenMP.

  References:
    - "A Survey of Monte Carlo Tree Search Methods" by Cameron Browne, Edward Powley, Daniel Whitehouse, Simon Lucas,
      Peter I. Cowling, Philipp Rohlfshagen, Stephen Tavener, Diego Perez, Spyridon Samothrakis, Simon Colton.
      IEEE Transactions on Computational Intelligence and AI in Games, 2012.

  Modified:
    8 de diciembre de 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

// Estructura para representar nodos del árbol
typedef struct OptionTreeNode {
    double value;
    int visits;
    struct OptionTreeNode* parent;
    struct OptionTreeNode** children;
    size_t num_children;
} OptionTreeNode;

// Declaraciones de funciones
double normalDistributionCumulative(double x);
double blackScholesPutPrice(double S, double K, double T, double r, double sigma);
double gaussianRandomNumber(void);
double simulateOptionPricing(double S, double K, double T, double r, double sigma);
OptionTreeNode* selectChild(OptionTreeNode* node);
OptionTreeNode* expandChild(OptionTreeNode* node);
void backpropagate(OptionTreeNode* node, double value);
double estimateOptionValueMCTS(double S, double K, double T, double r, double sigma, int numIterations, int numSims);



double blackScholesPutPrice(double S, double K, double T, double r, double sigma) {
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    double putPrice = K * exp(-r * T) * normalDistributionCumulative(-d2) - S * exp(-r * T) * normalDistributionCumulative(-d1);
    return putPrice;
}

double normalDistributionCumulative(double x) {
    return 0.5 * erfc(-x / sqrt(2.0));
}

double gaussianRandomNumber() {
    double u1 = rand() / (RAND_MAX + 1.0);
    double u2 = rand() / (RAND_MAX + 1.0);
    double s = u1 * sqrt(1.0 / 3.0) * u2;
    return s;
}

double simulateOptionPricing(double S, double K, double T, double r, double sigma) {
    // Simula un camino de precios usando el modelo de Black-Scholes
    double drift = exp((r - 0.5 * sigma * sigma) * T);
    double diffusion = sigma * sqrt(T) * gaussianRandomNumber();
    double simulatedPrice = S * drift * exp(diffusion);

    // Calcula el valor presente del payoff de la opción de venta
    double payoff = fmax(0.0, K - simulatedPrice);
    double discountedPayoff = payoff * exp(-r * T);

    return discountedPayoff;
}

OptionTreeNode* selectChild(OptionTreeNode* node) {
    // Selecciona el hijo con la mejor puntuación UCB (Upper Confidence Bound)
    double explorationParameter = 1.0;  // Ajusta según sea necesario
    OptionTreeNode* selectedChild = NULL;
    double bestScore = -1.0;

    for (size_t i = 0; i < node->num_children; ++i) {
        OptionTreeNode* child = node->children[i];
        double ucbScore = (child->value / child->visits) + explorationParameter * sqrt(log(node->visits) / child->visits);

        if (ucbScore > bestScore || selectedChild == NULL) {
            bestScore = ucbScore;
            selectedChild = child;
        }
    }

    return selectedChild;
}

OptionTreeNode* expandChild(OptionTreeNode* node) {
    // Expande un nodo seleccionando un nuevo camino aleatorio
    OptionTreeNode* newChild = malloc(sizeof(OptionTreeNode));
    newChild->value = 0.0;
    newChild->visits = 0;
    newChild->parent = node;
    newChild->children = NULL;
    newChild->num_children = 0;

    node->children = realloc(node->children, (node->num_children + 1) * sizeof(OptionTreeNode*));
    node->children[node->num_children++] = newChild;

    return newChild;
}

double simulateMonteCarlo(OptionTreeNode* node, double S, double K, double T, double r, double sigma, int numSims) {
    // Simula el valor de la opción usando Monte Carlo
    double totalPayoff = 0.0;
    
    for (int i = 0; i < numSims; ++i) {
        double discountedPayoff = simulateOptionPricing(S, K, T, r, sigma);
        totalPayoff += discountedPayoff;
    }

    return totalPayoff / numSims;
}

void backpropagate(OptionTreeNode* node, double value) {
    // Retropropaga los resultados hasta la raíz del árbol
    while (node != NULL) {
        node->visits += 1;
        node->value += value;
        node = node->parent;
    }
}

double estimateOptionValueMCTS(double S, double K, double T, double r, double sigma, int numIterations, int numSims) {
    OptionTreeNode* root = malloc(sizeof(OptionTreeNode));
    root->value = 0.0;
    root->visits = 0;
    root->parent = NULL;
    root->children = NULL;
    root->num_children = 0;

    // Medir el tiempo de inicio
    double start_time = omp_get_wtime();

    for (int i = 0; i < numIterations; ++i) {
        // Fase de selección y expansión
        OptionTreeNode* selectedNode = root;
        while (selectedNode->num_children > 0) {
            selectedNode = selectChild(selectedNode);
        }

        OptionTreeNode* expandedNode = expandChild(selectedNode);

        // Fase de simulación
        double simulatedValue = simulateMonteCarlo(expandedNode, S, K, T, r, sigma, numSims);

        // Fase de retropropagación
        backpropagate(expandedNode, simulatedValue);
    }

    // Medir el tiempo de finalización
    double end_time = omp_get_wtime();

    // Calcular el tiempo transcurrido en segundos
    double elapsed_time = end_time - start_time;

    // Selección del mejor resultado
    OptionTreeNode* bestChild = NULL;
    double bestVisits = -1.0;

    for (size_t i = 0; i < root->num_children; ++i) {
        OptionTreeNode* child = root->children[i];
        if (child->visits > bestVisits || bestChild == NULL) {
            bestVisits = child->visits;
            bestChild = child;
        }
    }

    double estimatedOptionValue = bestChild->value / bestChild->visits;

    // Liberar la memoria
    free(root);

    // Imprimir el tiempo transcurrido
    printf("Tiempo transcurrido: %f segundos\n", elapsed_time);


    return estimatedOptionValue;
}

int main() {
    // Semilla para la generación de números aleatorios
    srand((unsigned int)time(NULL));

    // Parámetros del modelo
    double S = 100.0; // Precio inicial del activo subyacente
    double K = 110.0; // Precio de ejercicio de la opción
    double T = 1.0;   // Tiempo de vencimiento (en años)
    double r = 0.05;  // Tasa de interés
    double sigma = 0.2; // Volatilidad del activo subyacente
    int numIterations = 10000; // Número de iteraciones de MCTS
    int numSims = 100000; // Número de simulaciones Monte Carlo por iteración

    // Valor de la opción utilizando Monte Carlo Tree Search
    double estimatedOptionValue = estimateOptionValueMCTS(S, K, T, r, sigma, numIterations, numSims);

    printf("Precio estimado de la opcion de venta (put): %f\n", estimatedOptionValue);

    return 0;
}
