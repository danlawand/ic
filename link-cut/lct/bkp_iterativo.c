#include <stdio.h>
#include <stdlib.h>
#include "lct.h"

static void *mallocSafe(size_t);
#define TAMANHO_MAX 200


int main(int argc, char * argv[]) {
	// if (argc < 2) {
	// 	printf("It needs the file's name.\n");
	// 	exit(EXIT_FAILURE);
	// }
	// FILE *arquivo_entrada;
	// arquivo_entrada = fopen(argv[1], "r");
	// if (arquivo_entrada == NULL) {
	// 	perror("Error while opening the file.\n");
	// 	exit(EXIT_FAILURE);
	// }
	// printf("%s\n", argv[1]);
	// char buffer[TAMANHO_MAX];
	
	// int n_vertices;
	
 //    while(fscanf(arquivo_entrada, "%s", buffer) && !feof(arquivo_entrada)){ /* le do arquivo */
 //    	printf("%s\n",buffer);
    	
 //    }


	int n_vertices;
	Node q;

	printf("Numero de Vertices:\n");
	scanf(" %d",&n_vertices);

	lctInit();
	Node *represented_tree;
	represented_tree = mallocSafe(n_vertices*sizeof(Node));


	for (int i = 0; i < n_vertices; ++i) {
		represented_tree[i] = maketree();
	}



	link(represented_tree[0], represented_tree[1]);

	analisaSplay(represented_tree[0]);
	printf("\n");

	printSPLAY(represented_tree[0], 1);
	printf("\n");


	link(represented_tree[0], represented_tree[2]);
	
	analisaSplay(represented_tree[0]);
	printf("\n");

	printSPLAY(represented_tree[0], 1);
	printf("\n");
	printf("\n");

	link(represented_tree[0], represented_tree[3]);
	
	analisaSplay(represented_tree[0]);
	printf("\n");

	printSPLAY(represented_tree[0], 1);
	printf("\n");
	printf("\n");

	link(represented_tree[4], represented_tree[5]);
	
	analisaSplay(represented_tree[4]);
	printf("\n");

	printSPLAY(represented_tree[4], 1);
	printf("\n");
	printf("\n");




	for (int i = 0; i < n_vertices; ++i)
	{
		analisaNode(represented_tree[i]);
	}
	// fclose (arquivo_entrada);
}

static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		printf("Erro: alocação de memória falhou no módulo node.\n");
		exit(0);
	}
	return p;
}