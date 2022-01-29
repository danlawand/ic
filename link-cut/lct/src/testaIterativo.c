#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lct.h"
#include <analisaLct.h>

static void *mallocSafe(size_t);
#define TAMANHO_MAX 200


int main(int argc, char * argv[]) {
	if (argc < 3) {
		printf("It needs the file's name and the test number.\n");
		exit(EXIT_FAILURE);
	}
	if (argc < 2) {
		printf("It needs the file's name.\n");
		exit(EXIT_FAILURE);
	}

	FILE *arquivo_entrada;
	FILE * arquivo_de_saida;

	// Lê o arquivo de entrada
	arquivo_entrada = fopen(argv[1], "r");

	// Verifica se o arquivo de entrada existe
	if (arquivo_entrada == NULL) {
		perror("Error while opening the file of arquivo_entrada.\n");
		exit(EXIT_FAILURE);
	}

	// Operacao para gerar o nome do arquivo do resultado do i-ésimo teste
	char output_file_name[] = "result_tests/result_test";
    strcat(output_file_name,argv[2]);
    printf("\n Result test file name: %s\n", output_file_name);

	// Abre o arquivo de saída
	arquivo_de_saida = fopen (output_file_name, "w");

	// Verifica se a criação do arquivo de saída foi bem sucedida
	if (arquivo_de_saida == NULL) {
		perror("Error while opening the file arquivo_de_saida.\n");
		exit(EXIT_FAILURE);
	}


	//buffer para o arquivo de entrada
	char buffer[TAMANHO_MAX];

	// identifica quantos nós teremos
	int n_vertices;

	//variáveis auxiliares
	int indice[2], tag_link = 2, tag_cut = 0, i = 1;
	indice[0] = 0;
	indice[1] = 0;

	//iniciamos a nossa LinkCutTree (lct)
	lctInit();

	Node *nodes;


	/* le do arquivo */
    while(fscanf(arquivo_entrada, "%s", buffer) && !feof(arquivo_entrada)){

    	//Se for a primeira iteração, pegaremos a primeira linha do arquivo que é a quantidade de nós
    	if (i){
    		n_vertices = atoi(buffer);

    		nodes = mallocSafe(n_vertices*sizeof(Node));

    		//Crio 'n_vertices' árvores com apenas um vértice cada (Cada nodes[i] é a raiz de sua árvore)
    		for (int i = 0; i < n_vertices; ++i) {
				nodes[i] = maketree();
			}

    		printf("%d Vertices Criados\n",n_vertices);
    	}
    	i = 0;
    	//Vou pegar de dois em dois vértices para fazer a operação.
    	//tag_link indica qual vértice eu estou me referindo, se for zero equivale ao primeiro, se for 1 ao segundo
    	if (tag_link < 2) {
    		//Identifico o índice do vértice que realizaremos a operação, e atribuo no indice[0] ou indice[1]
    		indice[tag_link] = atoi(buffer);

    		//Quando identificarmos o segundo nó, façamos:
    		if (tag_link == 1) {
    			//realizaremos o link do nó com índice indice[0] + nó com índice indice[1]
    			printf("----- Link dos Vertices %d e %d -----\n",indice[tag_link-1], indice[tag_link]);

    			//garante que nodes[indice[0]] é a raiz
    			if(findRoot(nodes[indice[tag_link-1]]) != nodes[indice[tag_link-1]]) {
    				evert(nodes[indice[tag_link-1]]);
    			}

	    		//Invariante: o indice[0] sempre será a raiz da árvore dele
    			link(nodes[indice[tag_link-1]], nodes[indice[tag_link]]);

    			analisaSplay(nodes[indice[tag_link-1]]);
				printf("\n");
				printSPLAY(nodes[indice[tag_link-1]], 1);
				printf("\n");
    		}
    		tag_link++;
    	}

    	//tag_cut indica se haverá cut ou não
    	if (tag_cut == 1) {
    		//Identifico o índice do vértice que realizaremos a operação, e atribuo no indice[0]
    		indice[0] = atoi(buffer);

    		printf("----- Cut do Vertice %d -----\n",indice[0]);

			//garante que nodes[indice[0]] não é a raiz
			if(findRoot(nodes[indice[0]]) != nodes[indice[0]]) {

				//Invariante: o indice[0] nunca é a raiz da árvore dele
    			cut(nodes[indice[0]]);
			}

			analisaSplay(nodes[indice[0]]);
			printf("\n");
			printSPLAY(nodes[indice[0]], 1);
			printf("\n");

    		tag_cut++;
    	}


    	if (buffer[0] == '+') {
    		tag_link = 0;
    		tag_cut = 0;
    	}

    	if (buffer[0] == '-') {
    		tag_cut = 1;
    		tag_link = 2;
    	}

    }

	printf("\n------------- Print Final ---------------- \n\n");
	for (int i = 0; i < n_vertices; ++i)
	{
		//Analiso cada nó, para ver como foi seu comportamento.
		analisaNode(nodes[i], arquivo_de_saida);
	}
	fclose(arquivo_de_saida);

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