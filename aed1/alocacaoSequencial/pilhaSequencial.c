#include <stdio.h>
#include <string.h>

#define TAM_MAX 5 

typedef struct cliente {
    char nome[255];
    float salario;
} Cliente;

int isPilhaCheia(int *topo);
int isPilhaVazia(int *topo);
void push(Cliente pilha[], int *topo);
void pop(Cliente pilha[], int *topo);

int main(void) {
    Cliente pilha[TAM_MAX];
    int topo = 0;
    push(pilha, &topo);
    push(pilha, &topo);
    push(pilha, &topo);
    push(pilha, &topo);
    push(pilha, &topo);
    push(pilha, &topo);
    pop(pilha, &topo);
    pop(pilha, &topo);
    pop(pilha, &topo);
    pop(pilha, &topo);
    pop(pilha, &topo);
    pop(pilha, &topo);
    return 0;
}

void pop(Cliente pilha[], int *topo) {
    if(!isPilhaVazia(topo)) {
        (*topo)--;
    } else {
        printf("Pilha vazia!\n");
        return;
    }
}

void push(Cliente pilha[], int *topo) {
    if(!isPilhaCheia(topo)) {
        Cliente c;
        printf("Nome: ");
        fgets(c.nome, 255, stdin);
        printf("Salario: ");
        scanf("%f", &(c.salario));
        pilha[*topo] = c;
        (*topo)++;
        getchar();
    } else {
        printf("Pilha cheia!\n");
        return;
    }
}

int isPilhaVazia(int *topo) {
    return (*topo==0);
}

int isPilhaCheia(int *topo) {
    return ((*topo<TAM_MAX) ? 0 : 1);
}
