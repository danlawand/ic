#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay.h"

#define TAMANHO_MAX 200

int compareString(char* s1, char* s2) {
	if(!strcmp(s1, s2)) return 1;
	return 0;
}


int main(int argc, char * argv[]) {
	FILE *arquivo_saida, *arquivo_entrada;
	int n;
	Value val;
	int tamanho = strlen(argv[1]);
	int tam = strlen(argv[1]);
	char *nome = malloc(sizeof(char)*(tamanho+tam-4));
	/* O Valor de -4 é por conta do size of '.txt'  */

	char buffer[TAMANHO_MAX];
    char * copia;

	for (int i = 0; i < tam-4; i++) {
		nome[i] = argv[1][i];
	}  
	for (int i = tam; i < tamanho+tam-4; i++) {
		nome[i] = argv[1][i-tam];
	}

	arquivo_entrada = fopen(argv[1], "r");
	arquivo_saida = fopen (nome,"w");

	if (arquivo_entrada == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	int chave, valor, insercao, remocao, busca;
	insercao = 0;
	remocao = 0;
	busca = 0;

    while(fscanf(arquivo_entrada, "%s", buffer) && !feof(arquivo_entrada)){ /* le do arquivo */
    	if (compareString(buffer,"i")) {
    		insercao = 1;
	    	printf("\n%s ",buffer);
    	} else if (compareString(buffer,"r")) {
    		remocao = 1;
	    	printf("\n%s ",buffer);
    	} else if (compareString(buffer,"g")) {
    		busca = 1;
	    	printf("\n%s ",buffer);
    	} else if (insercao >= 1) {
    		if (insercao == 1) {
    			chave = atoi(buffer);
    			insercao++;
    		}
    		else {
    			valor = atoi(buffer);
    			fprintf(arquivo_saida, "\nInserção: Chave %d -- Valor %d\n", chave, valor);
				put(chave, valor);
    			insercao = 0;
    		}
    	} else if (remocao) {
			chave = atoi(buffer);
			delete(chave);
			fprintf(arquivo_saida, "\nRemoção: Chave %d\n", chave);
    		remocao = 0;
    	} else if (busca) {
			chave = atoi(buffer);
			val = get(chave);
			fprintf(arquivo_saida, "\nBusca: Chave %d -- Valor %d\n", chave, val);
			printValue(val);
    		busca = 0;
    	}
    	if (!insercao && !busca && !remocao) {
			fprintf(arquivo_saida, "Tamanho: %d\n", sizeSPLAY());
			print2D(arquivo_saida);
			printTree();
			printRoot();
    	}
    }
	printf("%d\n", sizeSPLAY());
	fclose (arquivo_saida);
	fclose (arquivo_entrada);
}
