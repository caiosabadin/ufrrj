#include <stdio.h>
#include <string.h>

#define TAM_MAX 2

typedef struct cliente {
    char nome[255];
    float salario;
} Cliente;

int isFilaCheia(int *fim);
int isFilaVazia(int *fim);
void inserir(Cliente fila[], int *fim);
void remover(Cliente fila[], int *fim);

int main(void) {
    Cliente clientes[TAM_MAX];
    int fim = 0;
    inserir(clientes, &fim);
    inserir(clientes, &fim);
    inserir(clientes, &fim);
    remover(clientes, &fim);
    remover(clientes, &fim);
    remover(clientes, &fim);
    return 0;
}

void remover(Cliente fila[], int *fim) {
    if(!isFilaVazia(fim)) {
        int i = 0;
        for(i=0;i<(*fim-1);i++) {
            fila[i] = fila[i+1];
        }
        (*fim)--;
    } else  {
        printf("Fila vazia!\n");
        return;
    }
}

void inserir(Cliente fila[], int *fim) {
    if(!isFilaCheia(fim)) {
        
        Cliente c;
        printf("Nome: ");
        fgets(c.nome, 255, stdin);
        printf("Salario: ");
        scanf("%f", &(c.salario));
        getchar();

        fila[*fim] = c;
        (*fim)++;
    } else {
        printf("Fila cheia!\n");
        return;
    }
}

int isFilaVazia(int *fim) {
    return (*fim==0);
}

int isFilaCheia(int *fim) {
    return (*fim==TAM_MAX);
}
