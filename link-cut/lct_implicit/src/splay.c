#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

// children[1] == right
// children[0] == left
static int valor;
static Node  root; 				/*root of Splay Tree*/

static Node sibling(Node);

static void swapChildren(Node);

static void pushBitUp(Node);

static void pushBitDown(Node);

static void  rotate(Node);

static Node maximum(Node);

static Node minimum(Node);

void splayInit() {
	valor = 0;
}

Node makeSplay() {
	// if (chave == 'Z') chave = 'a';
	return newNode(valor++, NULL, NULL, NULL, NULL, 0, 0);
}

// Uso essa rotina no evert
// O objetivo dessa rotina é alterar o bit de v, para que indique que os filhos serão invertidos.
// Ou seja:
//
//      9:0             7:0
//    8:0       ===>>       9:0
//  7:1                   8:0
//
// Porém, é preciso com que se realize o pushbitDown, para que se mantenha a ordem correta na árvore
// Assim, o bit irá se propagar pela árvore
//
//      9:0         7:0               7:0             7:0
//    8:0     ===>>     9:0   ===>>     8:0   ===>>     8:0
//  7:1               8:1                 9:1             9:0
//
void reflectTree(Node v) {
	v->bit = 1 - v->bit;
	pushBitDown(v); // para que a raiz da LCT fique com o bit zero
}

// A prinxípio w não tem filho direito (w->children[1] == NULL)
void join(Node v, Node w) {
	v->children[1] = w;
	w->parent = v;
}


// Na splay: Separo o nó x de seus filhos direitos, o que significa que estou separando x e o nó direito que é mais profundo.
// Ou seja, na LCT estou cortando o vínculo de x com seu pai
void split(Node x) {
	Node T;

	T = x->children[1 - x->bit];
	if (T != NULL) {
		T->parent = NULL;

		// Pq inverto os bits?
		T->bit ^= x->bit;
	}
	x->children[1 - x->bit] = NULL;
}


void splay (Node x) {
	while (x->parent != NULL) {

		Node p = x->parent;

		//If the father is the root
		if (p->parent == NULL) rotate(x);


		//If It's the left child and it's parent is the left child
		//If It's the right child and it's parent is the right child
		else if (( p == p->parent->children[0] && x == p->children[p->bit] ) ||
		( p == p->parent->children[1] && x == p->children[1 - p->bit] )) {
			rotate(p);
			rotate(x);
		}

		//If It's the left child and it's parent is the right child
		//If It's the right child and it's parent is the left child
		else {
			rotate(x);
			rotate(x);
		}
	}
	pushBitDown(x);
	// x->parent == NULL, and only the root parent is NULL
	root = x;
}


static void rotate(Node x) {
	// inverto bit do pai e do irmão
	// E inverto quem é o filho [0] e o filho [1]
	if (x->bit == 1) pushBitUp(x);

	// pai
	Node p = x->parent;

	// Avô
	Node g = p->parent;

	//rightRotate
	// x filho esquerdo se torna o pai de seu pai
	if (p->children[0] == x) {

		//
		p->children[0] = x->children[1];
		if (x->children[1] != NULL) x->children[1]->parent = p;
		x->children[1] = p;
	}
	//leftRotate
	// x filho direito se torna o pai de seu pai
	else {
		p->children[1] = x->children[0];
		if (x->children[0] != NULL) x->children[0]->parent = p;
		x->children[0] = p;
	}
	x->bit = p->bit;
	p->bit = 0;

	p->parent = x;
	x->parent = g;
	if (g != NULL) {
		if (p == g->children[0]) g->children[0] = x;
		else g->children[1] = x;
	}
}

// Operação dumb Serve apenas para o print
Node minimumSemMudanca(Node x) {
	if (x->children[x->bit] == NULL) return x;
	return minimumSemMudanca(x->children[x->bit]);
}

Node minSplay(Node x) {
	Node m = minimum(x);
	splay(m);
	return m;
}


// recebe uma raiz e devolve o mínimo da árvore toda
static Node minimum(Node x) {
	// Será que não deveria acumular o bit quando faz o mínimo.
	pushBitDown(x);
	if (x->children[x->bit] == NULL) return x;
	return minimum(x->children[x->bit]);
}



Node maxSplay(Node x) {
	Node m = maximum(x);
	splay(m);
	return m;
}

// recebe uma raiz e devolve o máximo da árvore toda
static Node maximum(Node x) {
	// TESTAR SE PRECISA DO pushBitDown aqui, ou não
	pushBitDown(x);
	if (x->children[1-x->bit] == NULL) return x;
	return maximum(x->children[1-x->bit]);
}


/************************   AUXILIARY FUNCTIONS ************************/

// A ideia é "jogar" o bit de x (que é 1, no caso do rotate) para o pai 'p', por isso "p->bit = 1 - p->bit;"

// [PERGUNTA] - Por que inverto o bit do irmão? ---> Será que é porque eu faço swapChildren ?

// inverte o bit do pai, inverte o bit do irmão e depois inverto os irmãos: 'x' com 's'
// Invariante: o bit de x é 1
static void pushBitUp(Node x) {
	printf("--------------\n");
	printf("pushBitUp(%d) com bit 1\n", x->val);
	printf("--------------\n\n");
	Node p = x->parent;
	p->bit = 1 - p->bit;
	Node s = sibling(x);
	if (s != NULL) s->bit = 1 - s->bit;
	swapChildren(p);
	x->bit = 0;
}


static void pushBitDown(Node x) {
	if (x->bit == 1) {
		printf("--------------\n");
		printf("pushBitDown(%d) com bit 1\n", x->val);
		printf("--------------\n\n");
		swapChildren(x);
		x->bit = 0;

		Node cLeft = x->children[0];
		if (cLeft != NULL) {
			cLeft->bit = 1 - cLeft->bit;
		}

		Node cRight = x->children[1];
		if (cRight != NULL) {
			cRight->bit = 1 - cRight->bit;
		}
	}
}

// devolve o irmão de x
static Node sibling(Node x) {
	Node p = x->parent;
	if (p->children[0] == x) return p->children[1];
	else return p->children[0];
}

// inverte os filhos
static void swapChildren(Node p) {
	Node aux = p->children[0];
	p->children[0] = p->children[1];
	p->children[1] = aux;
}


/************************   PRINT FUNCTIONS ************************/

void printSPLAY(Node x, int i) {
	if (x != NULL) {
		Node child;
		child  = x->children[0];
		if (child != NULL) child->bit ^= x->bit;
		child  = x->children[1];
		if (child != NULL) child->bit ^= x->bit;

		printSPLAY(x->children[1 - x->bit], i+1);
		int bparent = 0;
		if (x->parent != NULL) {
			bparent = x->parent->bit;
		}
		printf("%*d:%d\n", 2*i, x->val, x->bit^bparent);
		printSPLAY(x->children[x->bit], i+1);

		child  = x->children[0];
		if (child != NULL) child->bit ^= x->bit;
		child  = x->children[1];
		if (child != NULL) child->bit ^= x->bit;
	}
}
