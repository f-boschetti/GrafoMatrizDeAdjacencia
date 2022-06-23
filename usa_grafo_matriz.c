/*
 * Tarefa 02 - Fila
 *
 * GEN254 - Grafos - 2022/1
 *
 * Nome:      XXXX
 * Matricula: XXXX
 */

#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "grafo.h"
#include "fila.h"

int main() {
    int E;
    int V;
    int O;
    int X;
    Grafo *grafo;
    Aresta aresta;

    scanf("%d %d", &V, &E);
    grafo = GRAFOconstroi(V);

    for (int i = 0; i < E; i++){
        scanf("%d %d", &aresta.v1, &aresta.v2);
        GRAFOinsere_aresta(grafo, aresta);
    }
    
    scanf("%d", &O);

    for (int i = 0; i < O; i++){
        scanf("%d", &X);
        GRAFOimprime_distancias_caminhos(grafo, X);
    }

    GRAFOdestroi(grafo);

    return 0;
}