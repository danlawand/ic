#include "splay.h"
#include "printTree.h"
#include <stdio.h>
#include <stdlib.h>

// children[1] == right
// children[0] == left
static int   bit = 1;
static Node  root; 				/*root of Splay Tree*/
static Node  split_roots[2];

static int   size(Node);

static Node putRec(Node, Key, Value);

static Value getValue(Node, Key);
static Node  getNode(Node, Key);
static void  rotate(Node);

static Node  maximum(Node); 
static Node  join(Node, Node);
static Node* split(Node);
static void  delete(Node);
static void  printSPLAY(Node, int);
static void pushBitDown(Node);
static int compareKeys(Key, Key);


int sizeSPLAY() {
	return size(root);
}

Key maxSPLAY() {
	if (root == NULL) return keyNull();
	return maximum(root)->key;
}

Value getSPLAY(Key key) {
	Node x = getNode(root, key);
	if (root != NULL) splay(x);
	return x->val;
}

void putSPLAY(Key key, Value val) {
	Node x;
	x = putRec(root, key, val);
	if (root == NULL) root = x;
	splay(x);
	// x->bit = 1;
}

void deleteSPLAY(Key key) {
	Node x = getNode(root, key);
	if (x == NULL) return;
	delete(x);
	printf("Remocao completa da chave: %d\n", key);
}

void revertSPLAY() {
	bit = -bit;
	root->bit = 1 - root->bit;
}

int compareKeys(Key k1, Key k2) {
	return bit * (k1 - k2);
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
	// x->parent == NULL, and only the root parent is NULL
	root = x;
}

int isRoot(Node x) {
	if (x->parent == NULL) return 1;
	return 0;
}


/************************   AUXILIARY FUNCTIONS ************************/
static int size(Node x) {
	if (x == NULL) return 0;
	return x->N;
}

static Value getValue(Node x, Key key) {
	if (x == NULL) return valueNull();
	int cmp = compareKeys(key, x->key);
	
	if (cmp == 0) return x->val;
	
	Node child;
	if (cmp < 0) child = x->children[x->bit];	
	else child = x->children[1 - x->bit];		

	if (child != NULL) child->bit ^= x->bit;

	Value gV;
	gV = getValue(child, key);
	
	if (child != NULL) child->bit ^= x->bit;
	return gV;
}

//getPredecessor pq se x não estiver na arvore, eu faço splay no predecessor

static Node getNode(Node x, Key key) {
	if (x == NULL) return NULL;
	int cmp = compareKeys(key, x->key);

	if (cmp == 0) return x;

	Node child;
	if (cmp < 0) child = x->children[x->bit];	
	else child = x->children[1 - x->bit];		

	if (child != NULL) child->bit ^= x->bit;

	Node gN;
	gN = getNode(child, key);
	
	if (child != NULL) child->bit ^= x->bit;
	return gN;
}

static Node putRec(Node x, Key key, Value val) {
	if (x == NULL) {
		x = newNode(key, val, NULL, NULL, NULL, NULL, 0, 1);
		return x;
	}

	pushBitDown(x);

	int cmp = compareKeys(key, x->key);

	if (cmp == 0) { 
		x->val = val;
		return x;
	}

	Node child;
	if (cmp < 0) child = x->children[0];

	else child = x->children[1];		

	Node gN;
	gN = putRec(child, key, val);
	
	if (child == NULL) {
		gN->parent = x;
		if (cmp < 0) x->children[0] = gN;
		else x->children[1] = gN;
	}
	return gN;
}

static Node sibling(Node x) {
	Node p = x->parent;
	if (p->children[0] == x) return p->children[1];
	else return p->children[0];
}

static void swapChildren(Node p) {
	Node aux = p->children[0];
	p->children[0] = p->children[1];
	p->children[1] = aux;
}

static void pushBitUp(Node x) {
	Node p = x->parent;
	p->bit = 1 - p->bit;
	Node s = sibling(x);
	if (s != NULL) s->bit = 1 - s->bit;
	swapChildren(p);
	x->bit = 0;
}


static void pushBitDown(Node x) {
	if (x->bit == 1) {
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

//Talvez tenha que considerar o bit do 'p'
static void rotate(Node x) {
	if (x->bit == 1) pushBitUp(x);

	Node p = x->parent;
	Node g = p->parent;
	if (p->children[0] == x) {
		
		p->children[0] = x->children[1];
		if (x->children[1] != NULL) x->children[1]->parent = p;
		x->children[1] = p;
	}
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



//All the items in S are smaller than the items in T
static Node join(Node S, Node T) {
	if (S == NULL) return T;
	if (T == NULL) return S;

	Node x = maximum(S);
	splay(x);

	x->children[1] = T;
	T->parent = x;

	//x is the root of the joining tree
	// x->N = size(x->children[1]) + size(x->children[0]) + 1;
	return x;
}

static Node maximum(Node x) {
	pushBitDown(x);
	if (x->children[1] == NULL) return x;
	return maximum(x->children[1]);
}

//Assumimos que o 
static Node* split(Node x) {
	Node S, T;
	splay(x);
	
	printf("--Split--\n");
	printSPLAY(x, 1);
	printf("---------\n");

	T = x->children[1 - x->bit];
	if (T != NULL) {
		T->parent = NULL;
		T->bit ^= x->bit;
	}	
	x->children[1 - x->bit] = NULL;
	S = x;

	// x = NULL;

	split_roots[0] = S;
	split_roots[1] = T;
	// printf("--S--\n");
	// printSPLAY(S, 1);
	// printf("---------\n");
	// printf("--T--\n");
	// printSPLAY(T, 1);
	// printf("---------\n");

	return split_roots;
}

// Pré-condição é que x != NULL
static void delete(Node x) {

	Node* trees;
	trees = split(x);
	Node w = trees[0]->children[trees[0]->bit];

	//x->left->parent = x
	if (w != NULL) w->parent = NULL;

	root = join(w, trees[1]);
	trees[0] = NULL;
	trees[1] = NULL;
	x = NULL;
}

/************************   PRINT FUNCTIONS ************************/

void printTree(FILE *pFile) {
	if (pFile != NULL) print2D(root, pFile);
	printSPLAY(root, 1);
}


void printRoot() {
	if(root != NULL) printf("Root é: Chave: %d -- Valor: %d\n", root->key, root->val);
	else printf("Root é NULL\n");
}


static void printSPLAY(Node x, int i) {
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
