FILE *abreArquivo(char *modo) {
	FILE *arq = fopen(NOME_ARQUIVO, modo);
	if(arq != NULL) {
        return arq;
    }
    else {
        exit(EXIT_FAILURE);
    }
}

void fechaArquivo(FILE *arq) {
	fclose(arq);
}

void gravaAlbum(Album *album) {
	FILE *arq = abreArquivo("a");
	fprintf(arq, "%s;%s;%d;%.1f;", getTitulo(album), getBanda(album), getAno(album), getNota(album));
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
    fprintf(arq, "\n");
    fechaArquivo(arq);
}

int numeroAlbuns(void) {
	FILE *arq = abreArquivo("r+");
	int i = 0;
	char *album = (char *)malloc(sizeof(char)*LINHA);

	while(fgets(album, LINHA, arq)) {
		i++;
	}

	free(album);
	fechaArquivo(arq);
	return i;	
}

char **leAlbuns(void) {
	FILE *arq = abreArquivo("r+");
	char **albuns = (char **)malloc(TOTAL_ALBUNS*sizeof(char *));
	int i = 0;
	for(i=0;i<TOTAL_ALBUNS;i++) {
		albuns[i] = (char *)malloc(sizeof(char)*LINHA);
	}
	char *album = (char *)malloc(sizeof(char)*LINHA);
	i = 0;
	while(fgets(album, LINHA, arq)) {
		album[strcspn(album, "\n")]=0;
		strcpy(albuns[i], album);
		i++;
	}
	free(album);
	fechaArquivo(arq);
	return albuns;
}

void editaArquivo(int posicao, Album *albumEditado) {

	// guarda todos os albuns do arquivo original nessa variavel
	char **albuns = leAlbuns();
	int total = numeroAlbuns();
	FILE *arq = abreArquivo("w"); // reinicia o arquivo

	// grava todos os albuns ate a posicao do album editado
	int i = 0;
	for(i=0;i<posicao;i++) {
		fputs(albuns[i], arq);
		fputs("\n", arq);
	}
	
	fechaArquivo(arq);

	// grava o album editado
	gravaAlbum(albumEditado);

	// aumenta i para i pular de "POSICAO" para o proximo
	// valor depois de POSICAO
	i++;

	// grava os albuns apos o album editado
	arq = abreArquivo("a");

	for(;i<total;i++) {
		fputs(albuns[i], arq);
		fputs("\n", arq);
	}
	fechaArquivo(arq);

	// limpa os mallocs que fez

	for(i=0;i<total;i++) {
		free(albuns[i]);
	}
	free(albuns);
}

void deletaArquivo(int posicao) {

	// guarda todos os albuns do arquivo original nessa variavel
	char **albuns = leAlbuns();
	int total = numeroAlbuns();
	FILE *arq = abreArquivo("w"); // reinicia o arquivo

	// grava todos os albuns ate a posicao do album deletado
	int i = 0;

	// este if serve para o caso da linha nao estar na primeira
	// posicao do arquivo
	if(i!=posicao) {
		for(i=0;i<posicao;i++) {
			fputs(albuns[i], arq);
			fputs("\n", arq);
		}
	}
	fechaArquivo(arq);

	// aumenta i para i pular de "POSICAO" para o proximo
	// valor depois de POSICAO, assim nao escrevendo o
	// album que esta em POSICAO, deletando-o, pois
	i++;

	// grava os albuns apos o album deletado
	arq = abreArquivo("a");

	for(;i<total;i++) {
		fputs(albuns[i], arq);
		fputs("\n", arq);
	}
	fechaArquivo(arq);

	// limpa os mallocs que fez
	for(i=0;i<total;i++) {
		free(albuns[i]);
	}
	free(albuns);
}