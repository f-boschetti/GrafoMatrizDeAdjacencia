#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

struct grafo {
    int num_vertices;
    int num_arestas;
    int **matriz_adj;
};

int **constroi_matriz_int(int m, int n) {
    int **matriz = malloc(m * sizeof(*matriz));
    for (int i = 0; i < m; i++) {
        matriz[i] = malloc(n * sizeof(*(matriz[i])));
        for (int j = 0; j < n; j++) {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

void destroi_matriz_int(int **matriz, int m) {
    for (int i = 0; i < m; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

bool GRAFOvertice_valido(Grafo *g, int v) {
    if ((v >= 0) && (v <= (g->num_vertices - 1))) {
        return true;
    }

    return false;
}

bool GRAFOaresta_valida(Grafo *g, Aresta e) {
    if (GRAFOvertice_valido(g, e.v1) && GRAFOvertice_valido(g, e.v2)) {
        return true;
    }

    return false;
}

Grafo *GRAFOconstroi(int num_vertices) {
    Grafo *g = malloc(sizeof(*g));

    g->num_vertices = num_vertices;
    g->num_arestas = 0;
    g->matriz_adj = constroi_matriz_int(num_vertices, num_vertices);

    return g;
}

int GRAFOnum_vertices(Grafo *g) {
    return g->num_vertices;
}

int GRAFOnum_arestas(Grafo *g) {
    return g->num_arestas;
}

bool GRAFOtem_aresta(Grafo *g, Aresta e) {
    if (!GRAFOaresta_valida(g, e)) {
        printf("Erro na operacao GRAFOtem_aresta: a aresta %d %d eh "
            "invalida!\n", e.v1, e.v2);
        exit(EXIT_FAILURE);
    }

    return (g->matriz_adj[e.v1][e.v2] != 0);
}

void GRAFOinsere_aresta(Grafo *g, Aresta e) {
    if (!GRAFOaresta_valida(g, e)) {
        printf("Erro na operacao GRAFOinsere_aresta: a aresta %d %d eh "
            "invalida!\n", e.v1, e.v2);
        exit(EXIT_FAILURE);
    }

    if (GRAFOtem_aresta(g, e) || (e.v1 == e.v2)) {
        return;
    }

    g->matriz_adj[e.v1][e.v2] = 1;
    g->matriz_adj[e.v2][e.v1] = 1;

    g->num_arestas++;
}

void GRAFOremove_aresta(Grafo *g, Aresta e) {
    if (!GRAFOaresta_valida(g, e)) {
        printf("Erro na operacao GRAFOremove_aresta: a aresta %d %d eh "
            "invalida!\n", e.v1, e.v2);
        exit(EXIT_FAILURE);
    }

    if (!GRAFOtem_aresta(g, e)) {
        return;
    }

    g->matriz_adj[e.v1][e.v2] = 0;
    g->matriz_adj[e.v2][e.v1] = 0;

    g->num_arestas--;
}

void GRAFOdestroi(Grafo *g) {
    destroi_matriz_int(g->matriz_adj, g->num_vertices);

    free(g);
}

void GRAFObusca_larg(Grafo *g, int v, int pai[], int dist[]) {
    int marcado[g->num_vertices];
    for (int i = 0; i < g->num_vertices; i++)
        marcado[i] = 0;
    Fila *f = FILAconstroi();
    marcado[v] = 1;
    pai[v] = -1;
    dist[v] = 0;
    FILAinsere(f, v);
    while (!FILAvazia(f)) {
        int w = FILAremove(f);
        for (int u = 0; u < g->num_vertices; u++)
            if (g->matriz_adj[w][u] != 0 )
                if (marcado[u] == 0) {
                    marcado[u] = 1; 
                    pai[u] = w;
                    dist[u] = dist[w] + 1;
                    FILAinsere(f, u);
                }
    }
}

void GRAFOimprime_distancias_caminhos(Grafo *g, int x){
    int pai[g->num_vertices];
    int dist[g->num_vertices];
    for (int i = 0; i < g->num_vertices; i++){
        pai[i] = -1;
        dist[i] = __INT_MAX__;
    }
    GRAFObusca_larg(g, x, pai, dist);

    for (int i = 0; i < g->num_vertices; i++){
        printf("%d: ", i);
        if(dist[i] != __INT_MAX__){
            printf("%d,", dist[i]);
            int atual = i;
            while (atual != -1){
                printf(" %d", atual);
                atual = pai[atual];
            }
            printf("\n");
        }else{
            printf("infinita, sem caminho ate %d\n", x);
        }
        
    }
    
}
