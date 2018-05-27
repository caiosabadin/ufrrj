#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int valor;
    struct no *prox;
    struct no *anterior;
} No;

No *criaLista(int valor);
No *insere(int valor, No *lista);
void limpaLista(No *lista);
void exibeLista(No *lista);
No *removeInicio(No *lista);
No *removeFim(No *lista);
No *removeLista(int valor, No *lista);

int main(void) {
    No *lista = criaLista(1);
    lista = insere(2, lista);
    lista = insere(3, lista);
    lista = insere(4, lista);
    lista = insere(5, lista);
    lista = insere(6, lista);
    lista = insere(7, lista);
    
    lista = removeInicio(lista);
    lista = removeFim(lista);
    
    lista = removeLista(10, lista);
    lista = removeLista(2, lista);
    lista = removeLista(6, lista);
    lista = removeLista(4, lista);

    exibeLista(lista);
    
    limpaLista(lista);
    
    return 0;
}

No *removeLista(int valor, No *lista) {
    if((((lista->prox==NULL)&&(lista->anterior==NULL))||(lista==NULL))&&(lista->valor==valor)) {
        return NULL;
    } else {
        No *aux = lista;
        int encontrado = 0;
        
        do {
            if(aux->valor==valor) {
                encontrado=1;
                break;
            } else {
                aux = aux->prox;
            }
        } while(aux!=lista);

        if((aux==lista)&&(!encontrado)) {
            printf("Nao encontrado!\n");
        } else {
           No *anterior = aux->anterior;
           No *proximo = aux->prox;
           anterior->prox = proximo;
           proximo->anterior = anterior;
           if(aux==lista) {
                lista = proximo;
           }
           free(aux);
        }

        return lista;
    }
}

No *removeFim(No *lista) {
    if(((lista->prox==NULL)&&(lista->anterior==NULL))||(lista==NULL)) {
        return NULL;
    } else {
        No *ultimo = lista->anterior;
        No *aux = ultimo->anterior;
        aux->prox = lista;
        lista->anterior = aux;
        free(ultimo);
    }
    return lista;
}

No *removeInicio(No *lista) {
    if(((lista->prox==NULL)&&(lista->anterior==NULL))||(lista==NULL)) {
        return NULL;
    } else {
        No *ultimo = lista->anterior;
        No *aux = lista->prox;
        ultimo->prox = aux;
        aux->anterior = ultimo;
        free(lista);
        lista = aux;
    }
    return lista;
}

void exibeLista(No *lista) {
    No *aux = lista;
    while(aux->prox!=lista) {
        printf("%d\n", aux->valor);
        aux = aux->prox;
    }
    printf("%d\n", aux->valor);
}

void limpaLista(No *lista) {
    No *aux = lista;

    while(aux->prox!=lista) {
        No *ultimo = lista->anterior;
        aux = lista->prox;
        aux->anterior = ultimo;
        ultimo->prox = aux;
        free(lista);
        lista = aux;
    }
    free(lista);
}

No *insere(int valor, No *lista) {
    No *no = (No *)malloc(sizeof(No));
    no->valor = valor;

    if((lista->prox==NULL)&&(lista->anterior==NULL)) {
        no->prox = lista;
        lista->anterior = no;
        no->anterior = lista;
        lista->prox = no;
    } else {
        No *ultimo = lista->anterior;
        no->anterior = ultimo;
        ultimo->prox = no;
        lista->anterior = no;
        no->prox = lista;
    }

    lista = no;
    return lista;
}

No *criaLista(int valor) {
    No *no = (No *)malloc(sizeof(No));
    no->valor = valor;
    no->prox = NULL;
    no->anterior = NULL;
    return no;
}
