#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splay.h"

#define TAMANHO_MAX 200

int main(int argc, char * argv[]) {
	FILE *arquivo_saida, *arquivo_entrada;
	int n;
	Value val;
	int tamanho = strlen(argv[1]);
	int tam = strlen(argv[1]);
	char *nome = malloc(sizeof(char)*(tamanho+tam));
	char buffer[TAMANHO_MAX];
    char * copia;

    if (argc < 1) {
		printf("It needs the file's name.\n");
		exit(EXIT_FAILURE);
    }

	for (int i = 0; i < tam; i++) {
		nome[i] = argv[1][i];
	}  
	for (int i = tam; i < tamanho+tam; i++) {
		nome[i] = argv[1][i-tam];
	}

	arquivo_entrada = fopen(argv[1], "r");
	arquivo_saida = fopen (nome,"w");

	if (arquivo_entrada == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}


    while(fscanf(arquivo_entrada, "%s", buffer) && !feof(arquivo_entrada)){ /* le do arquivo */
    	printf("%s\n",buffer);
    	copia = buffer;
    }
/*
	// while((ch = fgetc(fp)) != EOF) {
	// 	if (ch >= 48 && ch <= 57) {

	// 	} else if (ch == 'i') {

	// 	} else if (ch == 'r') {

	// 	} else if (ch == 'g') {

	// 	} else {
	// 		continue;
	// 	}
	// }

	// int chave, valor;
	// char c = '0';
	// while(c != 's') {
	// 	printf("(i)nserir (r)emover (g)et ou (s)air?\n");
	// 	scanf(" %c",&c);
	// 	if (c == 'i') {
	// 		printf("Digite: #chave #valor \n");
	// 		scanf(" %d",&chave);
	// 		scanf(" %d",&valor);
	// 		fprintf(arquivo_saida, "\nInserção: Chave %d -- Valor %d\n", chave, valor);
	// 		put(chave, valor);
	// 	} else if (c == 'r') {
	// 		printf("Digite a chave para Remocao:\n");
	// 		scanf(" %d",&chave);
	// 		delete(chave);
	// 		fprintf(arquivo_saida, "\nRemoção: Chave %d\n", chave);
	// 	} else if (c == 'g') {
	// 		printf("Digite a chave para busca:\n");
	// 		scanf(" %d",&chave);
	// 		val = get(chave);
	// 		fprintf(arquivo_saida, "\nBusca: Chave %d -- Valor %d\n", chave, val);
	// 		printValue(val);
	// 	} else if (c == 't') {
	// 		printf("%d\n", sizeSPLAY());
	// 	}
	// 	fprintf(arquivo_saida, "Tamanho: %d\n", sizeSPLAY());
	// 	print2D(arquivo_saida);
	// 	printTree();
	// 	printRoot();
	// }
	// printf("%d\n", sizeSPLAY());
	// fclose (arquivo_saida);
	fclose (arquivo_entrada);
*/
}