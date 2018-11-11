#include <stdio.h>
#define TAM 8

int isIndiceValido(int x, int y, int tabuleiro[TAM][TAM]);
void imprimeTabuleiro(int tabuleiro[TAM][TAM]);
int resolveCaminho(int x, int y, int movimento, int tabuleiro[TAM][TAM], int dx[8], int dy[8]);

int main(void) {
    int tabuleiro[TAM][TAM];
    int x = 0;
    int y = 0;

    /* preenche todo o tabuleiro como zero, indicando que
     * todas as casas ainda nao foram visitadas
     */
    for(x=0;x<TAM;x++) {
        for(y=0;y<TAM;y++) {
            tabuleiro[x][y] = -1;
        }
    }

    printf("Informe x0: ");
    int x0 = 0; scanf("%d", &x0);
    printf("Informe y0: ");
    int y0 = 0; scanf("%d", &y0);

    /* indica que a posicao inicial foi visitada */
    tabuleiro[x0][y0] = 0;

    /* dx e dy define quantas posicoes a mais ou a menos
     * de x e de y configuram um movimento valido para o
     * cavalo, que anda em L
     */
    int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    /* a partir daqui, resolveCaminho() se chamara recursivamente
     * ate que haja solucao ou a funcao retorne false, indicando
     * que nao ha solucao alguma disponivel a partir da posicao
     * inicial dada
     */
    if(resolveCaminho(x0, y0, 1, tabuleiro, dx, dy) == 0) {
        printf("Nao ha solucao possivel.\n");
    }
    else {
        imprimeTabuleiro(tabuleiro);
    }

    return 0;
}

int resolveCaminho(int x, int y, int contMovimento, int tabuleiro[TAM][TAM], int dx[8], int dy[8]) {
    
    /* se o numero de movimentos for igual a quantidade
     * total de caminhos possiveis (TAM ao quadrado),
     * isto significa que o algoritmo percorreu todas as
     * casas do tabuleiro possiveis.
     */
    if(contMovimento==(TAM*TAM)) {
        return 1;
    }

    int k = 0;
    int proxX = 0;
    int proxY = 0;

    /* testa os 8 possiveis movimentos do cavalo, recursivamente */
    for(k=0;k<8;k++) {
        proxX = x + dx[k];
        proxY = y + dy[k];

        if(isIndiceValido(proxX, proxY, tabuleiro)) {
            tabuleiro[proxX][proxY] = contMovimento;
            if(resolveCaminho(proxX, proxY, contMovimento+1, tabuleiro, dx, dy) == 1) {
                return 1;
            }
            else {
                tabuleiro[proxX][proxY] = -1;
            }
        }    
    }

    return 0;
}

void imprimeTabuleiro(int tabuleiro[TAM][TAM]) {
    int x = 0;
    int y = 0;
    for(x=0;x<TAM;x++) {
        printf("|");
        for(y=0;y<TAM;y++) {
            printf(" %2d ", tabuleiro[x][y]);
        }
        printf("|\n");
    }
}

/* esta funcao verifica se o indice que se tentara chamar e valido ou
 * nao, isto e, se ele esta dentro dos limites do tabuleiro e se este
 * indice, no tabuleiro, ja nao foi acessado antes.
 */
int isIndiceValido(int x, int y, int tabuleiro[TAM][TAM]) {
    return(x>=0 && x<TAM && y>=0 && y<TAM && tabuleiro[x][y]==-1);
}