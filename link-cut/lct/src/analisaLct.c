#include "analisaLct.h"
#include <stdio.h>

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay 
static void analisaPreOrdemSplay(Node x);

void quemEhDireito(Node x) {
	if (x == NULL) return;
	if(x->children[1 - x->bit] == NULL) {
		printf("%d Right Eh null\n",x->key);
	} else {
		printf("%d Right %d\n",x->key, x->children[1 - x->bit]->key);
	}
}

void quemEhEsquerdo(Node x) {
	if (x == NULL) return;
	if(x->children[x->bit] == NULL) {
		printf("%d Left Eh null\n",x->key);
	} else {
		printf("%d Left %d\n",x->key, x->children[x->bit]->key);
	}
}

void quemEhPai(Node x) {
	if (x == NULL) return;
	if(x->parent == NULL) {
		printf("%d parent Eh null\n",x->key);
	} else {
		printf("%d parent %d\n",x->key, x->parent->key);
	}
}

void quemEhPathParent(Node x) {
	if (x == NULL) return;
	if(x->pathParent == NULL) {
		printf("%d pathParent Eh null\n",x->key);
	} else {
		printf("%d pathParent %d\n",x->key, x->pathParent->key);
	}
}

// Sem a opção de imprimir em um arquivo
void analisaNode(Node x) {
	if (x == NULL) return;

	printf("Sobre o %d\n", x->key);
	quemEhDireito(x);
	quemEhEsquerdo(x);
	quemEhPai(x);
	quemEhPathParent(x);
	printf("\n");
	if (x->parent == NULL) {
		printSPLAY(x, 1);
		printf("\n");
	}
}

// Com a opção de imprimir em um arquivo
void analisa_Node_E_Imprime_em_arquivo(Node x, FILE *printFile) {
	if (x == NULL) return;

	printf("Sobre o %d\n", x->key);
	quemEhDireito(x);
	quemEhEsquerdo(x);
	quemEhPai(x);
	quemEhPathParent(x);
	printf("\n");
	if (x->parent == NULL) {
		printSPLAY(x, 1);
		printf("\n");
	}
}

void analisaSplay(Node x) {
	if (x == NULL) return;
	if (x->parent != NULL) x = findRoot(x);
	analisaPreOrdemSplay(x);
}

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay 
static void analisaPreOrdemSplay(Node x) {
	if (x == NULL) return;
	analisaNode(x);
	analisaPreOrdemSplay(x->children[1-x->bit]);
	analisaPreOrdemSplay(x->children[x->bit]);
}
