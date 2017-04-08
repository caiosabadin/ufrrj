typedef struct album {
    char *titulo;
    char *banda;
    int ano;
    float nota;
    char **generos;
} Album;

Album *newAlbum() {
	return ((Album *)malloc(sizeof(Album)));
}

void limpaAlbum(Album *album) {
	free(album->titulo);
	free(album->banda);
	int i = 0;
	while(album->generos[i]!=NULL) {
		free(album->generos[i]);
		i++;
	}
	free(album->generos);
	free(album);
}

char *getTitulo(Album *album) {
	return album->titulo;
}

char *getBanda(Album *album) {
	return album->banda;
}

int getAno(Album *album) {
	return album->ano;
}

float getNota(Album *album) {
	return album->nota;
}

char **getGeneros(Album *album) {
	return album->generos;
}

void setTitulo(Album *album, char *titulo) {
	album->titulo = (char *)malloc(sizeof(char)*BUFFER);
	strcpy(album->titulo, titulo);
}

void setBanda(Album *album, char *banda) {
	album->banda = (char *)malloc(sizeof(char)*BUFFER);
	strcpy(album->banda, banda);
}

void setAno(Album *album, int ano) {
	album->ano = ano;
}

void setNota(Album *album, float nota) {
	album->nota = nota;
}

void setGeneros(Album *album, char **generos) {
	album->generos = generos;
}

Album *leAlbum(void) {
	char *titulo = (char *)malloc(sizeof(char)*BUFFER);
	char *banda = (char *)malloc(sizeof(char)*BUFFER);
	int ano = 0;
	float nota = 0;
	char **generos =  (char **)malloc(BUFFER*sizeof(char *));
	Album *album = newAlbum();
	int i = 0;
	
	printf("Informe o nome do album: ");
	getchar(); // esse getchar elimina \ns soltos no buffer
	fgets(titulo, BUFFER, stdin);
	titulo[strcspn(titulo, "\n")]=0;
	setTitulo(album, titulo);

	printf("Informe o artista do album: ");
	fgets(banda, BUFFER, stdin);
	banda[strcspn(banda, "\n")]=0;
	setBanda(album, banda);

	printf("Informe o ano de lancamento do album: ");
	scanf("%d", &ano);
	getchar(); // esse getchar elimina o \n que o scanf acaba deixando solto no buffer
	setAno(album, ano);

	printf("Informe a nota do album: ");
	scanf("%f", &nota);
	getchar(); // esse getchar elimina o \n que o scanf acaba deixando solto no buffer
	setNota(album, nota);

	// le os generos

	while(TRUE) {
		printf("Informe o %do. genero do album (para parar, tecle 0): ", i+1);
		generos[i] = (char *)malloc(sizeof(char)*BUFFER);
		fgets(generos[i], BUFFER, stdin);
		generos[i][strcspn(generos[i], "\n")]=0;
		if(!strcmp(generos[i], "0")) {
			if(i==0) {
				strcpy(generos[i], "sem genero");
				generos[i+1] = (char *)malloc(sizeof(char)*BUFFER);
				strcpy(generos[i+1], "0");
			}
           	break;
       	}
       	i++;
	}
	setGeneros(album, generos);
	return album;
}