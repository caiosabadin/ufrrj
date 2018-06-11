#include <stdio.h>
#include <stdlib.h>

/*
 *
 * O selection sort trabalha não exatamente movendo valores, mas
 * sim analisando índices, para só então trocar os valores.
 * Basicamente, é um for que roda pegando do primeiro elemento do
 * vetor e indo até o penúltimo. Neste for, uma variável responsável
 * por pegar o menor índice recebe o valor do índice atual do for, o
 * qual é equivalente à variável i. Definido isto, passa-se a
 * executar outro laço for, desta vez pegando de um elemento a
 * frente do atual (i+1) até o último. Dentro deste segundo for,
 * deve-se comparar se o vetor na posição indiceMenor é maior do que
 * o da posição atual. Se for, então o da posição atual é menor, e,
 * por isto, deve-se armazenar seu índice (j) como o indiceMenor.
 * Ao fim do segundo for, troca-se o vetor na posição i (ou seja,
 * na posição corrente) pelo de menor índice.
 *
 */

void selectionSort(int vetor[], int tam) {
    int i = 0;
    int j = 0;
    for(i=0;i<tam-1;i++) {
        int indiceMenor = i;
        for(j=i+1;j<tam;j++) {
            if(vetor[indiceMenor] > vetor[j]) {
                indiceMenor = j;
            }
        }
        int aux = vetor[i];
        vetor[i] = vetor[indiceMenor];
        vetor[indiceMenor] = aux;
    }                  
}

void exibe(int vetor[], int tam) {
    int i = 0;
    for(i=0;i<tam;i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main(void) {
    int vetor[] = {3, 5, 2, 4, 1};
    selectionSort(vetor, 5);
    exibe(vetor, 5);
    return 0;
}
