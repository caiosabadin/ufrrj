#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *prox;
} No;

No *criaLista(void);
No *insere(No *lista, int valor);
No *removeInicio(No *lista);
No *removeFim(No *lista);
void imprime(No *lista);
void esvaziaLista(No *lista);

int main(void) {
    No *lst = criaLista();
    lst = insere(lst, 1);
    lst = insere(lst, 2);
    lst = insere(lst, 3);
    lst = insere(lst, 4);
    lst = insere(lst, 5);
    lst = removeInicio(lst);
    lst = removeFim(lst);
    imprime(lst);
    esvaziaLista(lst);
    return 0;
}

No *removeFim(No *lista) {
    if(lista==NULL) {
        printf("Lista vazia!\n");
        return NULL;
    }
    No *anterior = lista;
    No *proximo = anterior->prox;
    if(proximo==NULL) {
        return NULL;
    }
    while((proximo->prox)!=NULL) {
        anterior = anterior->prox;
        proximo = proximo->prox;
    }
    anterior->prox=NULL;
    free(proximo);
    return lista;
}

No *removeInicio(No *lista) {
    if(lista==NULL) {
        printf("Lista vazia!\n");
        return NULL;
    }
    No *aux = lista->prox;
    free(lista);
    return aux;
}

void esvaziaLista(No *lista) {
    No *aux = lista;
    while(aux!=NULL) {
        No *prox = aux->prox;
        free(aux);
        aux = prox;
    }
    free(lista);
    free(aux);
}

void imprime(No *lista) {
    No *aux = lista;
    while(aux!=NULL) {
        printf("Valor: %d.\n", aux->valor);
        aux=aux->prox;
    }
    free(aux);
}

No *insere(No *lista, int valor) {
    No *no = (No *)malloc(sizeof(No));
    if(!no) {
        printf("Sem espaco na memoria!\n");
        exit(1);
    }
    no->valor=valor;
    no->prox = lista;
    return no;
}

No *criaLista(void) {
    return NULL;
}