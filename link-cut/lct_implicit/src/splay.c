#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

// children[1] == right
// children[0] == left
static int   bit = 1;
static Node  root; 				/*root of Splay Tree*/
static Node  split_roots[2];

static Node sibling(Node);

static void swapChildren(Node);

static void pushBitUp(Node);

static void  rotate(Node);




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
	// x->parent == NULL, and only the root parent is NULL
	root = x;
}
// recebe uma raiz e devolve o mínimo da árvore toda
Node minimum(Node x) {
	// Será que não deveria acumular o bit quando faz o mínimo.
	if (x->children[x->bit] == NULL) return x;
	return minimum(x->children[x->bit]);
}


/************************   AUXILIARY FUNCTIONS ************************/

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


void pushBitDown(Node x) {
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


// SERÁ QUE O MÁXIMO NÃO É ASSIM?
// recebe uma raiz e devolve o máximo da árvore toda
// Node maximum(Node x) {
// 	// TESTAR SE PRECISA DO pushBitDown aqui, ou não
// 	pushBitDown(x);
// 	if (x->children[1-x->bit] == NULL) return x;
// 	return maximum(x->children[1-x->bit]);
// }


Node casquinhaMax(Node x) {
	maximum(x);
	splay(x);
}

// recebe uma raiz e devolve o máximo da árvore toda
Node maximum(Node x) {
	// TESTAR SE PRECISA DO pushBitDown aqui, ou não
	pushBitDown(x);
	if (x->children[1] == NULL) return x;
	return maximum(x->children[1]);
}

Node* split(Node x) {
	Node S, T;
	splay(x);

	T = x->children[1 - x->bit];
	if (T != NULL) {
		T->parent = NULL;

		// Pq inverto os bits?
		T->bit ^= x->bit;
	}
	x->children[1 - x->bit] = NULL;
	S = x;

	split_roots[0] = S;
	split_roots[1] = T;

	return split_roots;
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
