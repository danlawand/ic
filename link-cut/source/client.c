#include <stdio.h>
#include <stdlib.h>
#include "/home/daniel/ic/splay/source/splay.h"

int main(int argc, char * argv[]) {
   FILE * pFile;
   int n;
   Value val;
   pFile = fopen ("teste.txt","w");


	int chave, valor;
	char c = '0';
	initSplay();
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
		}
		fprintf(pFile, "Tamanho: %d\n", sizeSPLAY());
		print2D(pFile);
		printTree();
		printRoot();
	}
	printf("Tamanho: %d\n", sizeSPLAY());
	fclose (pFile);
}