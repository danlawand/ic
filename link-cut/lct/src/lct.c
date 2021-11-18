#include "lct.h"
#include <stdio.h>

static int chave;
static int valor;

// Funções auxiliares do access
static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay 
static void analisaPreOrdemSplay(Node x);


void lctInit() {
	chave = 0;
	valor = 0;
}

Node maketree() {
	return newNode(chave++, valor++, NULL, NULL, NULL, NULL, 0, 0);
}

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


// u e v estão em árvores distintas e v é a raiz da sua árvore; junta as árvores de u e v, acrescentando a aresta v->u. 
void link(Node v, Node w) {
	access(v);
	access(w);
	v->children[1 - v->bit] = w;
	w->parent = v;
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



/*****************************************/


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