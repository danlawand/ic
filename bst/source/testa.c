#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(int argc, char * argv[]) {
	int chave, valor;
	char c = '0';
	while(c != 's') {
		printf("(i)nserir (r)emover (g)et ou (s)air?\n");
		scanf(" %c",&c);
		if (c == 'i') {
			printf("Digite: #chave #valor \n");
			scanf(" %d",&chave);
			scanf(" %d",&valor);
			putBST(chave, valor);
		} else if (c == 'r') {
			printf("Digite a chave para Remocao:\n");
			scanf(" %d",&chave);
			deleteBST(chave);
		} else if (c == 'g') {
			printf("Digite a chave para busca:\n");
			scanf(" %d",&chave);
			printValue(getBST(chave));
		} else if (c == 't') {
			printf("%d\n", sizeBST());
		}
		printTree();
	}
	printf("%d\n", sizeBST());
}