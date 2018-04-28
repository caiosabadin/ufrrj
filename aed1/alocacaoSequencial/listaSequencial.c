#include <stdio.h>
#include <string.h>
#define TAM_MAX 2

typedef struct cliente {
    char nome[255];
    int id;
    float salario;
} Cliente;

int isEstourada(int n);
int buscaIndexNome(Cliente listaCliente[], int *tamanhoAtualLista, char nome[]);
int buscaIndexId(Cliente listaCliente[], int *tamanhoAtualLista, int id);
void inserir(Cliente listaCliente[], int *tamanhoAtualLista);
void remover(Cliente listaCliente[], int *tamanhoAtualLista);
void imprimir(Cliente listaCliente[], int *tamanhoAtualLista);

int main(void) {
    Cliente clientes[TAM_MAX];
    int tam = 0;
    
    inserir(clientes, &tam);
    inserir(clientes, &tam);
    inserir(clientes, &tam);

    remover(clientes, &tam);
    remover(clientes, &tam);

    inserir(clientes, &tam);
    imprimir(clientes, &tam);
    
    return 0;
}

int isEstourada(int n) {
    return ((n<TAM_MAX) ? 0 : 1);
}

void inserir(Cliente listaCliente[], int *tamanhoAtualLista) {
    if(!isEstourada(*tamanhoAtualLista)) {
        Cliente c;
        printf("Nome: ");
        fgets(c.nome, 255, stdin);
        printf("\nSalario: ");
        scanf("%f", &(c.salario));
        printf("\nId: ");
        scanf("%d", &(c.id));
        listaCliente[*tamanhoAtualLista] = c;
        (*tamanhoAtualLista)++;
        getchar();
    } else {
        printf("A lista esta cheia!\n");
        return;
    }
}

int buscaIndexNome(Cliente listaCliente[], int *tamanhoAtualLista, char nome[]) {
    int i = 0;
    int indice = -1;
    for(i=0;i<(*tamanhoAtualLista);i++) {
        if(strcmp(listaCliente[i].nome, nome)==0) {
           indice = i;
        }
    }
    return indice;
}

int buscaIndexId(Cliente listaCliente[], int *tamanhoAtualLista, int id) {
    int i = 0;
    int indice = -1;
    int inferior = 0, superior = TAM_MAX;
    int meio = (inferior+superior)/2;
    
    while(inferior<=superior) {
        if(listaCliente[meio].id == id) {
            indice = meio;
            return indice;
        }
        else {
            if(id > listaCliente[meio].id) {
                inferior = meio+1;
            }
            else {
                superior = meio-1;
            }
        }
    }

    return indice;
}

void remover(Cliente listaCliente[], int *tamanhoAtualLista) {
    char nome[255];
    printf("Nome para buscar: ");
    fgets(nome, 255, stdin);
    int indexCliente = buscaIndexNome(listaCliente, tamanhoAtualLista, nome);
    if(indexCliente==-1) {
        printf("Nao encontrado!");
        return;
    }
    else {
        int i = 0;
        for(i=indexCliente;i<*tamanhoAtualLista-1;i++) {
            listaCliente[i] = listaCliente[i+1];
        }
        (*tamanhoAtualLista)--;
        printf("%s foi removido.\n", nome);
    }
}

void imprimir(Cliente listaCliente[], int *tamanhoAtualLista) {
    int id = 0;
    printf("Id para buscar: ");
    scanf("%d", &id);
    int indexCliente = buscaIndexId(listaCliente, tamanhoAtualLista, id);
    if(indexCliente==-1) {
        printf("Nao encontrado!");
        return;
    }
    else {
        Cliente c = listaCliente[indexCliente];
        printf("Nome: %s.\nSalario: %.2f.\nId: %d.\n", c.nome, c.salario, c.id);
    }
}
