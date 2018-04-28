#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *prox;
} No;

typedef struct fila {
    No *inicio;
    No *fim;
} Fila;

Fila *criaFila(void);
int isFilaVazia(Fila *f);
void inserir(Fila *f, int valor);
void remover(Fila *f);
void esvazia(Fila *f);

int main(void) {
    Fila *f = criaFila();
    inserir(f, 10);
    inserir(f, 20);
    inserir(f, 30);

    remover(f);
    remover(f);
    remover(f);
    remover(f);

    esvazia(f);
    return 0;
}

void remover(Fila *f) {
    if(isFilaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }
    No *aux = f->inicio;
    f->inicio = aux->prox;
    if(f->inicio==NULL) {
        f->fim=NULL;
    }
    free(aux);
}

void inserir(Fila *f, int valor) {
    No *no = (No *)malloc(sizeof(No));
    no->valor=valor;
    no->prox=NULL;

    if(isFilaVazia(f)) {
        f->fim=no;
        f->inicio=no;
    } else {
        No *aux = f->fim;
        aux->prox = no;
        f->fim = no;
    }
}

void esvazia(Fila *f) {
    No *aux= f->inicio;
    while(f->inicio!=NULL) {
        f->inicio=aux->prox;
        free(aux);
        aux=f->inicio;
    }
    free(aux);
    free(f);
}

int isFilaVazia(Fila *f) {
    return ((f->inicio==NULL)&&(f->fim==NULL));
}

Fila *criaFila(void) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}