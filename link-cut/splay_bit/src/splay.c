#include "splay.h"
#include "printTree.h"
#include <stdio.h>
#include <stdlib.h>

// children[0] == right
// children[1] == left
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
	putIterativo(key, val);
}

void deleteSPLAY(Key key) {
	Node x = getNode(root, key);
	if (x == NULL) return;
	delete(x);
	printf("Remocao completa da chave: %d\n", key);
}

// int childIndexNode(int bit_parent, int bit_child, int index_child) {
// 	if (bit_parent != bit_child) {
		
// 	}
// 	return alguma outra coisa
// }

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
	if (cmp < 0) return getValue(x->children[1], key);
	else if (cmp > 0) return getValue(x->children[0], key);
	else return x->val;
}

static Node getNode(Node x, Key key) {
	if (x == NULL) return NULL;
	int cmp = compareKeys(key, x->key);
	if (cmp < 0) return getNode(x->children[1], key);
	else if (cmp > 0) return getNode(x->children[0], key);
	else return x;
}

static void putIterativo(Key key, Value val) {
	if (root == NULL) {
		root = newNode(key, val, NULL, NULL, NULL, NULL, 1, 1);
		return;
	}
	Node v = root;
	Node q = root;
	int cmp, esq;
	esq = 0;
	while(1) {
		if (v == NULL) {
			v = newNode(key, val, NULL, NULL, q, NULL, 1, 1);
			if (esq) q->children[1] = v;
			else q->children[0] = v;

			while(q != NULL) {
				q->N = q->N + 1;
				q = q->parent;
			}
			
			break;
		} else {
			cmp = compareKeys(key, v->key);
			if (cmp < 0) {
				esq = 1;
				q = v;
				v = v->children[1];
			} else if (cmp > 0) {
				esq = 0;
				q = v;
				v = v->children[0];
			} else {
				v->val = val;
				break;
			}
		}
		
	}
	// v is the new node 
	// root is the same root
	splay(v);
	//root->key = v->key;

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