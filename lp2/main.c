#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "album.h"
#include "arquivo.h"

void limpaTela(void);
void cadastraAlbum(void);
int consultaAlbum(void);
void editaAlbum(int posicao);
void deletaAlbum(int posicao);
void verTodosAlbuns(void);
void retornaMenu(void);

int main(void) {
	int opt = 0, posicao = 0;
	limpaTela();
	while(TRUE) {
		printf("MENU\n<1> Cadastrar Album\n<2> Consultar Album\n<3> Ver Todos os Albuns\n<4> Sair\n>> ");
		scanf("%d", &opt);

		if(opt==1) {
			cadastraAlbum();
			printf("Album gravado com sucesso!");
			retornaMenu();
		}

		else if(opt==2) {
			posicao = consultaAlbum();
			if(posicao==0) {
				printf("Album nao encontrado!");
				retornaMenu();
			}
			else {
				posicao--; // corrige a soma de +1 ao i do metodo consultaAlbum()
				int opt2 = 0;
				while(TRUE) {
					printf("Selecione uma opcao: \n<1> Editar Album\n<2> Excluir Album\n<3> Voltar ao Menu\n>> ");
					scanf("%d", &opt2);
					if(opt2==1) {
						editaAlbum(posicao);
						printf("Album editado com sucesso!");
						retornaMenu();
						break;
					}
					else if(opt2==2) {
						limpaTela();
						printf("Voce tem >>CERTEZA<< de que quer >>DELETAR<< o album?\n>>NAO<< sera possivel recupera-lo depois!\n");
						printf("<1> Sim\n<Demais numeros> Nao!\n>> ");
						int certeza = 0; scanf("%d", &certeza);
						if(certeza==1) {
							deletaAlbum(posicao);
							printf("Album deletado com sucesso!");
						}
						retornaMenu();
						break;
					}
					else if(opt2==3) {
						break;
					}
					else {
						printf("Selecione uma opcao valida!\n\n");
					}
				}
				limpaTela();
			}
		}

		else if(opt==3) {
			verTodosAlbuns();
			printf("Todos os albuns foram exibidos.");
			retornaMenu();
		}

		else if(opt==4) {
			printf("Obrigado por usar o programa!");
			retornaMenu();
			exit(0);
		}

		else {
			printf("ESCOLHA UMA OPCAO VALIDA!");
			retornaMenu();
		}
	}
	return 0;
}

void retornaMenu(void) {
	printf("\nPressione Enter para continuar...\n");
	getchar(); getchar();
	limpaTela();
}

void verTodosAlbuns(void) {
	// guarda espaco e le os albuns guardados no arquivo
	char **albuns = (char **)malloc(sizeof(char *)*TOTAL_ALBUNS);
	int totalAlbuns = numeroAlbuns();
	int i = 0;
	int posicaoDoAlbumBuscadoNoArquivo = 0;
	for(i=0;i<totalAlbuns;i++) {
		albuns[i] = (char *)malloc(sizeof(char)*LINHA);
	}
	albuns = leAlbuns();

	char *albumCorrente = (char *)malloc(sizeof(char)*LINHA);
	for(i=0;i<totalAlbuns;i++) {
		Album *album = newAlbum(); // inicializa um struct de album
		char **generos = (char **)malloc(sizeof(char *)*LINHA); // inicializa um vetor de generos
		strcpy(albumCorrente, albuns[i]); // copia para albumCorrente o valor da primeira linha do arquivo
		char *token = strtok(albumCorrente, ";"); // tokeniza o texto do albumCorrente
			
		// essa variavel sera a variavel que indicara, respectivamente:
		// j = 0 indica o primeiro token pegado de albumCorrente, o titulo
		// j = 1 indica o segundo token, o artista
		// j = 2 indica o terceiro token, o ano
		// j = 3 indica o quarto token, a nota
		// j > 3 indica o n-esimo token, todos de cada genero guardado
		int controle = 0;

		// enquanto houver tokens para a linha atual, o while
		// gravara o token, conforme a variavel de controle,
		// em seu respectivo lugar do struct Album
		while(token!=NULL) {
			if(controle==0) {
				// significa que esta no titulo
				setTitulo(album, token);
			}

			else if(controle==1) {
				// significa que esta no artista
				setBanda(album, token);
			}

			else if(controle==2) {
				// significa que esta no ano
				// o strtol converte token,
				// uma string, para int
				setAno(album, strtol(token, NULL, 0));
			}

			else if(controle==3) {
				// significa que esta na nota
				// o strtof converte token,
				// uma string, para float
				setNota(album, strtof(token, NULL));
			}

			else {
				// se chegou aqui, e sinal de que aqui estao os generos

				// inicializa a primeira posicao de generos, que e
				// a mesma coisa que CONTROLE-4, visto que para
				// entrar neste else, CONTROLE é sempre >= 4
				generos[controle-4] = (char *)malloc(sizeof(char)*BUFFER); 

				// guarda o token no genero da vez
				strcpy(generos[controle-4], token);
			}

			// pega o proximo token, o que permite avançar no WHILE
			token = strtok(NULL, ";"); 
			controle++;
		}

		// o fim do while marca o fim de leitura da linha; todos as informacoes,
		// exceto os generos, ja foram gravadas; cabe, agora, grava-los, pois:
		setGeneros(album, generos);

		// aqui, ele apresentara o album recem-encontrado
		printf("Nome: %s.\nArtista: %s.\nAno: %d.\nNota: %.1f.\nGeneros: ", getTitulo(album), getBanda(album), getAno(album), getNota(album));
		int k = 0;
		// como o for anterior pegou um album e abaixo sao exibidos os generos deste album recem-encontrado,
		//a variavel "controle" subtraida de 4 unidades (uma para o titulo, outra para a banda, o ano e a
		// nota)indica a quantidade de generos lidos para o album encontrado 
		int totalGenerosLidos = controle-4;

		for(k=0;k<totalGenerosLidos;k++) {
			// significa que ele leu o ultimo genero
			if(k==(totalGenerosLidos-1)) {
				printf("%s.\n", getGeneros(album)[k]);	
			}
			else {
				printf("%s, ", getGeneros(album)[k]);
			}
		}

		// esse if apenas serve para garantir que a pessoa so precise apertar ENTER uma vez em todos os casos...
		// dois getchar() sao necessarios para i == 0 pois o primeiro deles consome um \n
		if (i==0) {
			getchar(); getchar();
		}
		else {
			getchar();
		}
	}
}

void deletaAlbum(int posicao) {
	deletaArquivo(posicao);
}

void editaAlbum(int posicao) {
	Album *albumEditado = leAlbum();
	editaArquivo(posicao, albumEditado);
	// esvazia os mallocs gerados em leAlbum()
	limpaAlbum(albumEditado);
}

int consultaAlbum(void) {
		char *tituloBuscado = (char *)malloc(sizeof(char)*BUFFER);
		char *bandaBuscada = (char *)malloc(sizeof(char)*BUFFER);
		
		printf("Digite o titulo do album buscado: ");
		getchar(); // esse getchar elimina \ns soltos no buffer
		fgets(tituloBuscado, BUFFER, stdin);
		tituloBuscado[strcspn(tituloBuscado, "\n")]=0;

		printf("Digite o nome do artista do album buscado: ");
		fgets(bandaBuscada, BUFFER, stdin);
		bandaBuscada[strcspn(bandaBuscada, "\n")]=0;
		
		// guarda espaco e le os albuns guardados no arquivo
		char **albuns = (char **)malloc(sizeof(char *)*TOTAL_ALBUNS);
		int totalAlbuns = numeroAlbuns();
		int i = 0;
		int posicaoDoAlbumBuscadoNoArquivo = 0;
		for(i=0;i<totalAlbuns;i++) {
			albuns[i] = (char *)malloc(sizeof(char)*LINHA);
		}
		albuns = leAlbuns();

		char *albumCorrente = (char *)malloc(sizeof(char)*LINHA);
		for(i=0;i<totalAlbuns;i++) {
			Album *album = newAlbum(); // inicializa um struct de album
			char **generos = (char **)malloc(sizeof(char *)*LINHA); // inicializa um vetor de generos
			strcpy(albumCorrente, albuns[i]); // copia para albumCorrente o valor da primeira linha do arquivo
			char *token = strtok(albumCorrente, ";"); // tokeniza o texto do albumCorrente
			
			// essa variavel sera a variavel que indicara, respectivamente:
			// j = 0 indica o primeiro token pegado de albumCorrente, o titulo
			// j = 1 indica o segundo token, o artista
			// j = 2 indica o terceiro token, o ano
			// j = 3 indica o quarto token, a nota
			// j > 3 indica o n-esimo token, todos de cada genero guardado
			int controle = 0;

			// enquanto houver tokens para a linha atual, o while
			// gravara o token, conforme a variavel de controle,
			// em seu respectivo lugar do struct Album
			while(token!=NULL) {

				if(controle==0) {
					// significa que esta no titulo
					setTitulo(album, token);
				}

				else if(controle==1) {
					// significa que esta no artista
					setBanda(album, token);
				}

				else if(controle==2) {
					// significa que esta no ano
					// o strtol converte token,
					// uma string, para int
					setAno(album, strtol(token, NULL, 0));
				}

				else if(controle==3) {
					// significa que esta na nota
					// o strtof converte token,
					// uma string, para float
					setNota(album, strtof(token, NULL));
				}

				else {
					// se chegou aqui, e sinal de que aqui estao os generos

					// inicializa a primeira posicao de generos, que e
					// a mesma coisa que CONTROLE-4, visto que para
					// entrar neste else, CONTROLE é sempre >= 4
					generos[controle-4] = (char *)malloc(sizeof(char)*BUFFER); 

					// guarda o token no genero da vez

					strcpy(generos[controle-4], token);
				}

				// pega o proximo token, o que permite avançar no WHILE
				token = strtok(NULL, ";"); 
				controle++;
			}

			// o fim do while marca o fim de leitura da linha; todos as informacoes,
			// exceto os generos, ja foram gravadas; cabe, agora, grava-los, pois:
			setGeneros(album, generos);

			// do lado de fora daquele while que le a linha e guarda ela formalmente no struct album,
			// voltamos ao nosso for que le todos os albuns; aqui se deve verificar se o titulo e o
			// artista do album lido batem com o que o usuario deseja, se baterem, ele guarda a variavel i, 
			// que indicara, neste caso, a posicao da linha que guarda o album no arquivo

			if(!strcmp(getTitulo(album), tituloBuscado)) {
				if(!strcmp(getBanda(album), bandaBuscada)) {
					posicaoDoAlbumBuscadoNoArquivo = i+1; // retorna i+1 pra caso a linha buscada seja i = 0
					limpaTela();

					// aqui, ele apresentara o album recem-encontrado
					printf("O resultado encontrado foi: \nNome: %s.\nArtista: %s.\nAno: %d.\nNota: %.1f.\nGeneros: ", getTitulo(album), getBanda(album), getAno(album), getNota(album));
					int k = 0;

					// como o for anterior para ao encontrar o album buscado, a variavel "controle" subtraida
					// de 4 unidades (uma para o titulo, outra para a banda, o ano e a nota) indica a quantidade
					// de generos lidos para o album encontrado 
					int totalGenerosLidos = controle-4;

					for(k=0;k<totalGenerosLidos;k++) {
						// significa que ele leu o ultimo genero
						if(k==(totalGenerosLidos-1)) {
							printf("%s.\n", getGeneros(album)[k]);	
						}
						else {
							printf("%s, ", getGeneros(album)[k]);
						}
					}
					return posicaoDoAlbumBuscadoNoArquivo;
				}
			}
		}
		// se nao encontrar nada, esse return retornara 0
		return posicaoDoAlbumBuscadoNoArquivo;

}

void cadastraAlbum(void) {
		Album *album = leAlbum();
		//grava o album
		gravaAlbum(album);
		// esvazia os mallocs gerados em leAlbum()
		limpaAlbum(album);
}

void limpaTela(void) {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}