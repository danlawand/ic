#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO_MAX 200
#define SAIR         "sair"
#define INSERE       "insere"
#define INFO         "info"
#define VIZINHO      "vizinho"
#define ARTICULACAOC "articulacao"
#define TAMC         "tamC"
#define PROMPT  printf(">>> ");

int alfabeto(char a){
    if(a == '-' || a == '\'' || a == '_' || a == '@')
        return 1;

    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
}


char lower(char a){
    if(a >= 'A' && a <= 'Z')
        return a - 'A' + 'a';

    return a;
}

/*
 * char * alocaPalavra(char * buffer)
 *
 * Trata a string salva em buffer e aloca
 * memoria para guarda-la.
 *
 * Retorna o endereco alocado
 *
 */
char * alocaPalavra(char ** buffer){
    char * palavra = NULL;
    int i = 0, j = 0, size = 0;

    for(i = 0; (*buffer)[i] != '\0' && !alfabeto((*buffer)[i]); i++);

    (*buffer) = (*buffer) + i;

    /* checa o tamanho da palavra */
    for(i = 0, size = 0; (*buffer)[i] != '\0' && alfabeto((*buffer)[i]); i++, size++);

    if(size > 0){
        palavra = malloc((size + 1)*sizeof(char));

        /* salva a palavra */
        for(i = 0, j = 0; (*buffer)[i] != '\0' && alfabeto((*buffer)[i]); i++)
            if(alfabeto((*buffer)[i]))
                palavra[j++] = lower((*buffer)[i]);

        palavra[size] = '\0';
        (*buffer) = (*buffer) + size;
    }


    return palavra;
}

void mostreUso(){
    printf("Para executar forneça o parâmetro k e o texto a ser lido.\n");
    printf("Exemplo:\n");
    printf("./ep4 k texto.txt\n");
}

void menu(){
    printf("\n----------------------------MENU---------------------------\n");
    printf("%s - recebe duas string a e b e devolve se são vizinhas\n", VIZINHO);
    printf("%s - insere a palavra digitada no grafo\n", INSERE);
    printf("%s - devolve se o vertice da string a e' uma articulacao\n", ARTICULACAOC);
    printf("%s - devolve o tamanho da componente da palavra digitada\n", TAMC);
    printf("%s - devolve as informacoes exigidas no enunciado\n", INFO);
    printf("%s - sai do programa\n", SAIR);
    printf("-----------------------------------------------------------\n");
    PROMPT;
}

int main(int argc, char * argv[]){
    int k, artic;
    char buffer[TAMANHO_MAX];
    int total = 0;
    char * copia;
    char * nome, * palavra, * b;
    double start, end, ellapsed;
    FILE * arquivo = NULL;

	if (argc != 2) {
		printf("FAILED Insufficient Number of Arguments\n");
		return 0;
	}
	nome = argv[1];
	printf("Arquivo de entrada %s\n", nome);
	arquivo = fopen(nome, "r");

	if(arquivo == NULL) {
   		printf("Ocorreu um erro, arquivo não pôde ser aberto.\n");
   		return 0;
	}
	printf("Arquivo aberto com sucesso!\n");

    while(fscanf(arquivo, "%s", buffer) && !feof(arquivo)){ /* le do arquivo */
	    copia = buffer;

	    while ((palavra = alocaPalavra(&copia)) != NULL){
	        total++;
	        printf("%s\n", palavra);
	        // insere(palavra);
	    }
    }
}
