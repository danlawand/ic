#include "lct.h"
#include <stdio.h>

static int chave;
static int valor;

// Funções auxiliares do access
static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

void lctInit() {
	chave = 0;
	valor = 0;
}

Node maketree() {
	if (chave == 'Z') chave = 'a';
	return newNode(chave++, valor++, NULL, NULL, NULL, NULL, 0, 0);
}

/*  removePreferredChild(Node v)
	// Imagine que estamos enviando o node, (key = 2 e v->bit = 0), da seguinte árvore
	//    4:0
	//  2:0
	//    1:0
	// Isso significa que removeremos o node 4 da árvore, e ele terá como pathParent o node 2
	// Com resultado:
	//  2:0
	//    1:0

	// O caso com v->bit = 1 seria:
	//    1:0
	//  2:1
	//    4:0
	// Com resultado
	//    1:0
	//  2:1
*/
static void removePreferredChild(Node v) {
	if (v->children[1 - v->bit] != NULL) {
		v->children[1 - v->bit]->pathParent = v;
		v->children[1 - v->bit]->parent = NULL;
	}
	v->children[1 - v->bit] = NULL;
}

static void switchPreferredChild(Node w, Node v) {
	if (w->children[1 - w->bit] != NULL) {
		w->children[1 - w->bit]->pathParent = v;
		w->children[1 - w->bit]->parent = NULL;
	}
	w->children[1 - w->bit] = v;
	v->parent = w;
	v->pathParent = NULL;
}

// Sleator refere ao access como expose(v)
//Acessa o nó v, criando o  preferred path da raiz até o nó v
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
	//v é raiz da splay tree do preferred path
}


// v e w estão em árvores distintas e v é a raiz da sua árvore;
// junta as árvores de v e w, acrescentando a aresta v->w, fazendo w pai de v (ou v filho de w).
void link(Node v, Node w) {
	access(v);
	access(w);
	w->children[1 - w->bit] = v;
	v->parent = w;
}

//Modifica a árvore que contém v para que v torne-se a raiz desta árvore
void evert(Node v) {
	access(v);
	//nó v é a raiz

	//reverte o bit
	//https://www.cs.cmu.edu/~sleator/papers/dynamic-trees.pdf
	// page 372
	v->bit = 1 - v->bit;
}

Node findRoot(Node v) {
	access(v);
	Node r = minimum(v);
	splay(r);
	return r;
}

//pré-condição: v não é uma raiz de árvore; remove a aresta v->parent(v).
void cut(Node v) {
	if (findRoot(v) == v) return;

	//acesso v, e v se torna raiz na sua splay tree
	access(v);

	// para garantir que o bit dele vá para o filho, se for 1
	pushBitDown(v);

	//realizo o split no pai do v, porque v->parent é menos profundo do que v, portanto v cai para o lado greater
	split(maximum(v->children[0]));
}
