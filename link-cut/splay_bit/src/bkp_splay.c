#include "splay.h"
#include "printTree.h"
#include <stdio.h>
#include <stdlib.h>

// children[1] == right
// children[0] == left
static Node  root; 				/*root of Splay Tree*/
static Node  split_roots[2];

static int   size(Node);
static void  putIterativo(Key, Value);
static Value getValue(Node, Key);
static Node  getNode(Node, Key);
static void  rotateRight(Node);
static void  rotateLeft(Node);
static Node  maximum(Node); 
static Node  join(Node, Node);
static Node* split(Node);
static void  delete(Node);
static void  printSPLAY(Node, int);

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
	x = putRec(key, val);
	splay(x);
}

void deleteSPLAY(Key key) {
	Node x = getNode(root, key);
	if (x == NULL) return;
	delete(x);
	printf("Remocao completa da chave: %d\n", key);
}


void splay (Node x) {
	while (x->parent != NULL) {
		
		//If the father is the root
		if (x->parent->parent == NULL) {

			//If it's the left child
			if (x == x->parent->children[1]) {
				// zig rotation
				rotateRight(x->parent);
			} 
			//If it's the right child
			else {
				// zag rotation
				rotateLeft(x->parent);
			}
		}
		//If It's the left child and it's parent is the left child
		else if (x == x->parent->children[1] && x->parent == x->parent->parent->children[1]) {
			// zig-zig rotation
			rotateRight(x->parent->parent);
			rotateRight(x->parent);
		}
		//If It's the right child and it's parent is the right child
		else if (x == x->parent->children[0] && x->parent == x->parent->parent->children[0]) {
			// zag-zag rotation
			rotateLeft(x->parent->parent);
			rotateLeft(x->parent);
		}
		//If It's the right child and it's parent is the left child
		else if (x == x->parent->children[0] && x->parent == x->parent->parent->children[1]) {
			// zig-zag rotation
			rotateLeft(x->parent);
			rotateRight(x->parent);
		}
		
		else {
			// zag-zig rotation
			rotateRight(x->parent);
			rotateLeft(x->parent);
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
	return gV
}

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
	return gN
}

static Node putRec(Node x, Key key) {
	if (x == NULL) {
		x = newNode(key, val, NULL, NULL, NULL, NULL, 0, 1);
		return x;
	}
	
	int cmp = compareKeys(key, x->key);

	if (cmp == 0) { 
		x->val = val;
		return x;
	}

	Node child;
	if (cmp < 0) child = x->children[x->bit];

	else child = x->children[1 - x->bit];		

	if (child != NULL) child->bit ^= x->bit;

	Node gN;
	gN = putRec(child, key);
	
	if (child != NULL) child->bit ^= x->bit;

	return gN
}

static void putIterativo(Key key, Value val) {
	if (root == NULL) {
		root = newNode(key, val, NULL, NULL, NULL, NULL, 0, 1);
		return;
	}
	Node v = root;
	Node q = root;
	int cmp, esq;
	esq = 0;
	while(1) {
		if (v == NULL) {
			v = newNode(key, val, NULL, NULL, q, NULL, 0, 1);
			if (esq) q->children[x->bit] = v;
			else q->children[1 - x->bit] = v;

			while(q != NULL) {
				q->N = q->N + 1;
				q = q->parent;
			}
			
			break;
		} else {
			cmp = compareKeys(key, v->key);
			if (cmp == 0) {
				v->val = val;
				break;
			}
			if (cmp < 0) {
				esq = 1 - x->bit;
				q = v;
				v = v->children[x->bit];
			} else {
				esq = x->bit;
				q = v;
				v = v->children[1 - x->bit];
			} 
		}
		
	}
	// v is the new node 
	// root is the same root
	splay(v);
	//root->key = v->key;

}


// Supondo qe estou no x e que o x->bit esta restaurado para o bit original
static void rotate(Node x) {
	p = x->parent;
	if p->children[p->bit] == x {
		p->children[p->bit] = x->children[1 - p->bit^x->bit]
		x->children[1 - p->bit^x->bit] = p
	}
	else { //similar para o: 1 - p->bit
		
	}	
}


static void rotateRight (Node h) {
	// x is the left child of parent h
	// We rotate h to the right
	// and h become rigth child of x 

	Node hParent = h->parent;

	Node x = h->children[1];
	h->children[1] = x->children[0];

	// A subarvore que era filha, agora é filha de h,
	// mas ela precisa saber quem é seu pai agr
	if (h->children[1] != NULL) h->children[1]->parent = h;

	x->children[0] = h;

	x->parent = h->parent;
	h->parent = x;

	if (hParent != NULL) {
		if (hParent->children[0] == h) {
			hParent->children[0] = x;
		} else {
			hParent->children[1] = x;
		}
	}

	x->N = h->N; 
	h->N = size(h->children[1]) + size(h->children[0]) + 1;
}

static void rotateLeft (Node h) {
	// x is the right child of parent h
	// We rotate h to the left
	// and h become left child of x 
	Node hParent = h->parent;

	Node x = h->children[0];
	h->children[0] = x->children[1];

	// A subarvore que era filha, agora é filha de h,
	// mas ela precisa saber quem é seu pai agr
	if (h->children[0] != NULL) h->children[0]->parent = h;

	x->children[1] = h;

	x->parent = h->parent;
	h->parent = x;

	if (hParent != NULL) {
		if (hParent->children[0] == h) {
			hParent->children[0] = x;
		} else {
			hParent->children[1] = x;
		}
	}

	x->N = h->N; 
	h->N = size(h->children[1]) + size(h->children[0]) + 1;
}


//All the items in S are smaller than the items in T
static Node join(Node S, Node T) {
	if (S == NULL) return T;
	if (T == NULL) return S;

	Node x = maximum(S);
	splay(x);

	x->children[0] = T;
	T->parent = x;

	//x is the root of the joining tree
	x->N = size(x->children[1]) + size(x->children[0]) + 1;
	return x;
}

static Node maximum(Node x) {
	if (x->children[0] == NULL) return x;
	return maximum(x->children[0]);
}

static Node* split(Node x) {
	Node S, T;
	splay(x);
	T = x->children[0];
	if (x->children[0] != NULL) T->parent = NULL;
	

	S = x;
	S->children[0] = NULL;
	S->N = size(S->children[1]) + 1;

	x = NULL;

	split_roots[0] = S;
	split_roots[1] = T;

	return split_roots;
}

// Pré-condição é que x != NULL
static void delete(Node x) {

	Node* trees;
	trees = split(x);

	//x->left->parent = x
	if (trees[0]->children[1] != NULL) trees[0]->children[1]->parent = NULL;

	root = join(trees[0]->children[1], trees[1]);
	trees[0] = NULL;
	trees[1] = NULL;
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
		printSPLAY(x->children[1], i+1);
		printf("%*d:%d\n", 2*i, x->val, x->N);
		printSPLAY(x->children[0], i+1);
	}
}