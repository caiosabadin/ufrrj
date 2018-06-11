#include <stdio.h>
#include <stdlib.h>

/*
 * O insertion sort funciona semelhantemente à maneira com que
 * ordenamos cartas em nossas mãos. Ele pegará, sempre, o segundo
 * valor do vetor (por isso o primeiro for começa com i = 1), e
 * percorrerá do segundo até o último elemento do vetor. O valor
 * atual do vetor será guardado em uma variável. Tendo-se guardado 
 * este, faz-se um for que irá comparar o valor atual com todos os
 * valores anteriores; enquanto houver um valor anterior maior que
 * o valor atual (isto é, enquanto houver um antecedente que seja
 * maior que o valor à sua frente), ele trocará um valor pelo
 * outro. Ao fim do processo, a última posição trocada receberá o
 * valor da variável atual. Isto é necessário porque o algoritmo
 * deixará duas posições com valores repetidos: a última trocada
 * e a anterior a ela. Ao se falar: vetor[j+1] = atual; diz-se:
 * já que houve uma troca, na posição anterior à da última troca,
 * coloque o valor atual, que é menor que o da última troca.
 *
 */

void insertionSort(int vetor[], int tam) {
    int i = 0;
    int j = 0;
    for(i=1;i<tam;i++) {
        int atual = vetor[i];
        for(j=i-1;j>=0 && vetor[j] > atual;j--) {
            vetor[j+1] = vetor[j];
        }
        vetor[j+1] = atual;
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
    insertionSort(vetor, 5);
    exibe(vetor, 5);
    return 0;
}
