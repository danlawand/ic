#include <stdio.h>
#include <stdlib.h>
#include "splay.h"

int main(int argc, char * argv[]) {
   FILE * pFile;
   Value val;
   pFile = fopen ("result_iterativo.txt","w");


	int chave, valor;
	char c = '0';

	while(c != 's') {
		printf("(i)nserir (r)emover (g)et ou (s)air?\n");
		scanf(" %c",&c);
		if (c == 'i') {
			printf("Digite: #chave #valor \n");
			scanf(" %d",&chave);
			scanf(" %d",&valor);
			fprintf(pFile, "\nInserção: Chave %d -- Valor %d\n", chave, valor);
			putSPLAY(chave, valor);
		} else if (c == 'r') {
			printf("Digite a chave para Remocao:\n");
			scanf(" %d",&chave);
			deleteSPLAY(chave);
			fprintf(pFile, "\nRemoção: Chave %d\n", chave);
		} else if (c == 'g') {
			printf("Digite a chave para busca:\n");
			scanf(" %d",&chave);
			val = getSPLAY(chave);
			fprintf(pFile, "\nBusca: Chave %d -- Valor %d\n", chave, val);
			printValue(val);
		} else if (c == 't') {
			printf("%d\n", sizeSPLAY());
		} else if (c == 'b') {
			revertSPLAY();
		}
		fprintf(pFile, "Tamanho: %d\n", sizeSPLAY());
		printTree(pFile);
		printRoot();
	}
	printf("Tamanho: %d\n", sizeSPLAY());
	fclose (pFile);
}