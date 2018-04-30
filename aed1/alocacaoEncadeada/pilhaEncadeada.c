#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *prox;
} No;

typedef struct pilha {
    No *topo;
} Pilha;

Pilha *criaPilha(void);
void push(Pilha *pilha, int valor);
void pop(Pilha *pilha);
int isPilhaVazia(Pilha *pilha);
void esvazia(Pilha *pilha);

int main(void) {
    Pilha *p = criaPilha();
    push(p, 10);
    push(p, 20);
    push(p, 30);
    pop(p);
    pop(p);
    esvazia(p);
    return 0;
}

void esvazia(Pilha *pilha) {
    if(isPilhaVazia(pilha)) {
        printf("Pilha vazia!\n");
        return;
    }
    No *aux = pilha->topo;
    while(aux!=NULL) {
        No *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    free(pilha);
}

void pop(Pilha *pilha) {
    if(!isPilhaVazia(pilha)) {
        No *aux = pilha->topo;
        pilha->topo = aux->prox;
        printf("Valor retirado: %d\n", aux->valor);
        free(aux);
    } else {
        printf("Pilha vazia!\n");
        return;
    }
}

int isPilhaVazia(Pilha *pilha) {
    return (pilha->topo==NULL);
}

void push(Pilha *pilha, int valor) {
    No *no = (No *)malloc(sizeof(No));
    no->valor=valor;
    no->prox = pilha->topo;
    pilha->topo = no;
}

Pilha *criaPilha(void) {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}