#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 255
#define TRUE 1

typedef struct album {
    char *titulo;
    char *banda;
    int ano;
    float nota;
    char **generos;
} Album;

FILE *abreArquivo(char *nome, char *modo) {
    FILE *arq = fopen(nome, modo);
    if(arq != NULL) {
        return arq;
    }
    else {
        exit(EXIT_FAILURE);
    }
}

void fechaArquivo(FILE *arquivo) {
    fclose(arquivo);
}

int contaAlbums(void) {
    FILE *arq = abreArquivo("teste.txt", "r+");
    char *linha = (char *)malloc(sizeof(char)*BUFFER);
    int i = 0;
    while(fgets(linha, sizeof(linha), arq)) {
        i++;
        if(!strcmp(linha, "\n")) {
            // o fgets vai contar duas linhas toda vez que
            // uma linha antiga terminar em \n, por isso,
            // foi necessario decrescer o valor de i toda
            // vez que isso acontecesse.
            i--;
        }
    }
    fechaArquivo(arq);
    return i/5;
}

Album **buscaAlbum(int opcao, char *termo) {
    int numAlbums = contaAlbums();
    if(opcao==1) {
        // busca por nome
    }
    else if(opcao==2) {
        // busca por banda
    }
    else if(opcao==3) {
        // busca por ano
    }
    else {
        // busca por genero
    }
}

Album *cadastraAlbum(void) {
    Album *album = (Album *)malloc(sizeof(Album));
    printf("Informe o nome do album: ");
    album->titulo = (char *)malloc(sizeof(char)*BUFFER);
    fgets(album->titulo, BUFFER, stdin);
    printf("Informe a banda ou artista do album: ");
    album->banda = (char *)malloc(sizeof(char)*BUFFER);
    fgets(album->banda, BUFFER, stdin);
    printf("Informe o ano do album: ");
    scanf("%d", &album->ano);
    printf("Informe a nota do album: ");
    scanf("%f", &album->nota);
    getchar(); // necessario pro primeiro fgets() do while abaixo funcionar
    int i = 0;
    album->generos = (char **)malloc(sizeof(char)*BUFFER);
    while(TRUE) {
        printf("Informe o %do. genero do album (para parar, tecle 0): ", i+1);
        album->generos[i] = (char *)malloc(sizeof(char)*BUFFER);
        fgets(album->generos[i], BUFFER, stdin);
        album->generos[i][strcspn(album->generos[i], "\n")]=0;
        if(!strcmp(album->generos[i], "0")) {
            break;
        }
        i++;
    }
    return album;
}

void gravaAlbum(void) {
    Album *album = cadastraAlbum();
    FILE *arq = abreArquivo("teste.txt", "w+");
    fprintf(arq, "%s", album->titulo);
    fprintf(arq, "%s", album->banda);
    fprintf(arq, "%d\n", album->ano);
    fprintf(arq, "%.2f\n", album->nota);
    int i = 0;
    while(TRUE) {
        char *genero = album->generos[i];
        if((genero!=NULL) && (strcmp(genero, "0")!=0)) {
           fprintf(arq, "%s;", genero); 
        }
        else {
            break;
        }
        i++; 
    }
    fechaArquivo(arq);
}

int main(void) {
    //gravaAlbum();
    printf("%d\n", contaAlbums());
    return 0;
}
