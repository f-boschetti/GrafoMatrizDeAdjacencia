/*
 * Tarefa 02 - Fila
 *
 * GEN254 - Grafos - 2022/1
 *
 * Nome:      XXXX
 * Matricula: XXXX
 */

/* Complete aqui */

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct elemFila {
    Item item;
    struct elemFila *proximo;
};
typedef struct elemFila ElemFila;

struct fila {
    ElemFila *topo;
    ElemFila *fim;
};

Fila *FILAconstroi() {
    Fila *f;
    f = malloc(sizeof(*f));
    f->topo = NULL;
    f->fim = NULL;
    return f;
}

bool FILAvazia(Fila *f) {
    return (f->topo == NULL);
}

void FILAinsere(Fila *f, Item i) {
    ElemFila *aux;
    aux = malloc(sizeof(*aux));
    aux->item = i;
    aux->proximo = NULL;
    if (FILAvazia(f)){
        f->topo = aux;
        f->fim = aux;
    }else {
        f->fim->proximo = aux;
        f->fim = aux;
    }
}

Item FILAremove(Fila *f) {
    Item i;
    ElemFila *aux;
    if (FILAvazia(f)) {
        printf("Erro na operacao FILAremove: fila vazia!\n");
        exit(EXIT_FAILURE);
    }
    i = f->topo->item;
    aux = f->topo;
    f->topo = f->topo->proximo;
    free(aux);
    return i;
}

void FILAdestroi(Fila *f) {
    ElemFila *aux;

    while (!FILAvazia(f)) {
        aux = f->topo;
        f->topo = f->topo->proximo;
        free(aux);
    }
    free(f);
}