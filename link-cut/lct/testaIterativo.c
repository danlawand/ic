#include <stdio.h>
#include <stdlib.h>
#include "lct.h"

static void *mallocSafe(size_t);
#define TAMANHO_MAX 200


int main(int argc, char * argv[]) {
	if (argc < 2) {
		printf("It needs the file's name.\n");
		exit(EXIT_FAILURE);
	}

	FILE *arquivo_entrada;
	arquivo_entrada = fopen(argv[1], "r");

	if (arquivo_entrada == NULL) {
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}

	char buffer[TAMANHO_MAX];
	int n_vertices, i = 1;
	int indice[2], tag_link = 2;
	indice[0] = 0;
	indice[1] = 0;
	
	Node q;

	lctInit();
	Node *represented_tree;
	


    while(fscanf(arquivo_entrada, "%s", buffer) && !feof(arquivo_entrada)){ /* le do arquivo */
    	if (i){ 
    		n_vertices = atoi(buffer);
    		
    		represented_tree = mallocSafe(n_vertices*sizeof(Node));
    		for (int i = 0; i < n_vertices; ++i) {
				represented_tree[i] = maketree();
			}

    		printf("%d Vertices Criados\n",n_vertices);
    	}
    	i = 0; 
    	if (tag_link < 2) {
    		indice[tag_link] = atoi(buffer);
    		if (tag_link == 1) {
    			printf("----- Link dos Vertices %d e %d -----\n",indice[tag_link-1], indice[tag_link]);
    			link(represented_tree[indice[tag_link-1]], represented_tree[indice[tag_link]]);
    			analisaSplay(represented_tree[indice[tag_link-1]]);
				printf("\n");
				printSPLAY(represented_tree[indice[tag_link-1]], 1);
				printf("\n");
    		}
    		tag_link++;
    	}
    	if (buffer[0] == '+') {
    		tag_link = 0;
    	}

    }








	// link(represented_tree[0], represented_tree[1]);

	// analisaSplay(represented_tree[0]);
	// printf("\n");

	// printSPLAY(represented_tree[0], 1);
	// printf("\n");


	// link(represented_tree[0], represented_tree[2]);
	
	// analisaSplay(represented_tree[0]);
	// printf("\n");

	// printSPLAY(represented_tree[0], 1);
	// printf("\n");
	// printf("\n");

	// link(represented_tree[0], represented_tree[3]);
	
	// analisaSplay(represented_tree[0]);
	// printf("\n");

	// printSPLAY(represented_tree[0], 1);
	// printf("\n");
	// printf("\n");

	// link(represented_tree[4], represented_tree[5]);
	
	// analisaSplay(represented_tree[4]);
	// printf("\n");

	// printSPLAY(represented_tree[4], 1);
	// printf("\n");
	// printf("\n");



	access(represented_tree[5]);
	for (int i = 0; i < n_vertices; ++i)
	{
		analisaNode(represented_tree[i]);
	}



	fclose (arquivo_entrada);
}

static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		printf("Erro: alocação de memória falhou no módulo node.\n");
		exit(0);
	}
	return p;
}