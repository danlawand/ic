#include "lct.h"
#include <stdio.h>

static int chave;
static int valor;

static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);
void lctInit() {
	chave = 0;
	valor = 0;
}

Node maketree() {
	return newNode(chave++, valor++, NULL, NULL, NULL, NULL, 0);
}

static void removePreferredChild(Node v) {
	if (v->right != NULL) {
		v->right->pathParent = v;
		v->right->parent = NULL;
	}
	//Muda o bit(?) reverse-bit
	//https://www.cs.cmu.edu/~sleator/papers/dynamic-trees.pdf 
	// page 372
	v->right = NULL;
}

static void switchPreferredChild(Node w, Node v) {
	if (w->right != NULL) {
		w->right->pathParent = v;
		w->right->parent = NULL;
	}
	w->right = v;
	v->parent = w;
	v->pathParent = NULL;
}

void access(Node v) {
	Node w;
	splay(v);
	printf("--\n");
	printSPLAY(v, 1);
	printf("--\n");

	removePreferredChild(v);

	while (v->pathParent != NULL) {
		w = v->pathParent;
		splay(w);
		switchPreferredChild(w, v);
		splay(v);

	}
}

void link(Node v, Node w) {
	access(v);
	access(w);
	v->right = w;
	w->parent = v;
}

/*
Reverse
*/

/*
Fazer evert, modifica a arvore que tem v, para essa
- evert(v): modifica a árvore que contém v para que v torne-se a raiz desta árvore
(reverte as arestas no caminho de v até a raiz da sua árvore). 
*/

/*****************************************/
void printSPLAY(Node x, int i) {
	if (x != NULL) {
		printSPLAY(x->left, i+1);
		// printf("%*d:%d\n", 2*i, x->val, x->N);
		printf("%*d\n", 2*i, x->val);
		printSPLAY(x->right, i+1);
	}
}


void quemEhDireito(Node x) {
	if (x == NULL) return;
	if(x->right == NULL) {
		printf("%d Right Eh null\n",x->key);
	} else {
		printf("%d Right %d\n",x->key, x->right->key);
	}
}

void quemEhEsquerdo(Node x) {
	if (x == NULL) return;
	if(x->left == NULL) {
		printf("%d Left Eh null\n",x->key);
	} else {
		printf("%d Left %d\n",x->key, x->left->key);
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

void analisaSplay(Node x) {
	if (x == NULL) return;
	analisaNode(x);
	analisaSplay(x->right);
	analisaSplay(x->left);
}