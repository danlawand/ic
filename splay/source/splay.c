#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

#define  COUNT	 						10
#define  INITIAL_NUM_SPLAY_TREES		 0

static Node  root; /*root of Splay Tree*/
static Node  split_roots[2];
static int   number_splay_trees = INITIAL_NUM_SPLAY_TREES;

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
static void  print2DUtil(Node, int, FILE*);

/*
	Estou pensando nas link-cut trees
	* Como saber onde eu adiciono um Node em uma splay tree
	sem indicar qual root?
	
	* Como armazenar as diferentes splay-trees?
	  R: linked-list of roots of splay trees?

*/


int initSplay() {
	int splay_id;
	root = NULL;
	splay_id = number_splay_trees;
	number_splay_trees++;

	return splay_id;
}

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
	delete(x);
	printf("Remocao completa da chave: %d\n", key);
}

void splay (Node x) {
	while (x->parent != NULL) {
		
		//If the father is the root
		if (x->parent->parent == NULL) {

			//If it's the left child
			if (x == x->parent->left) {
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
		else if (x == x->parent->left && x->parent == x->parent->parent->left) {
			// zig-zig rotation
			rotateRight(x->parent->parent);
			rotateRight(x->parent);
		}
		//If It's the right child and it's parent is the right child
		else if (x == x->parent->right && x->parent == x->parent->parent->right) {
			// zag-zag rotation
			rotateLeft(x->parent->parent);
			rotateLeft(x->parent);
		}
		//If It's the right child and it's parent is the left child
		else if (x == x->parent->right && x->parent == x->parent->parent->left) {
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
	if (x-parent == NULL) return 1;
	return 0;
}
/* ALGORITHMS OF https://www.cs.cmu.edu/~sleator/papers/dynamic-trees.pdf

Node parent(Node v) {
	return v->parent;
}

Node root(Node v) {
	Node w = v;
	while(v != NULL) {
		w = v;
		v = v->parent;
	}
	return w;
}


// Return  the  cost  of  the  edge  (v,parenf(v)). This operation  assumes that  v  is not  a  tree  root
int cost(Node v, Node p) {
	if (p == NULL) return 0;
	return p->val - v->val;
}

// Return the vertex w closest to root(v)  such  that  the  edge (w,parent(w))  
// has  minimum  cost  among  edges  on the  tree  path  from  v  to root(v). 
// This  operation  assumes that v  is  not  a  tree  root. 
Node mincost(Node v) {
	if 

}
*/
static int size(Node x) {
	if (x == NULL) return 0;
	return x->N;
}

static Value getValue(Node x, Key key) {
	if (x == NULL) return valueNull();
	int cmp = compareKeys(key, x->key);
	if (cmp < 0) return getValue(x->left, key);
	else if (cmp > 0) return getValue(x->right, key);
	else return x->val;
}

static Node getNode(Node x, Key key) {
	if (x == NULL) return NULL;
	int cmp = compareKeys(key, x->key);
	if (cmp < 0) return getNode(x->left, key);
	else if (cmp > 0) return getNode(x->right, key);
	else return x;
}

static void putIterativo(Key key, Value val) {
	if (root == NULL) {
		root = newNode(key, val, NULL, NULL, NULL, 1);
		return;
	}
	Node v = root;
	Node q = root;
	int cmp, esq;
	esq = 0;
	while(1) {
		if (v == NULL) {
			v = newNode(key, val, NULL, NULL, q, 1);
			if (esq) q->left = v;
			else q->right = v;

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
				v = v->left;
			} else if (cmp > 0) {
				esq = 0;
				q = v;
				v = v->right;
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

	Node x = h->left;
	h->left = x->right;

	// A subarvore que era filha, agora é filha de h,
	// mas ela precisa saber quem é seu pai agr
	if (h->left != NULL) h->left->parent = h;

	x->right = h;

	x->parent = h->parent;
	h->parent = x;

	if (hParent != NULL) {
		if (hParent->right == h) {
			hParent->right = x;
		} else {
			hParent->left = x;
		}
	}

	x->N = h->N; 
	h->N = size(h->left) + size(h->right) + 1;
}

static void rotateLeft (Node h) {
	// x is the right child of parent h
	// We rotate h to the left
	// and h become left child of x 
	Node hParent = h->parent;

	Node x = h->right;
	h->right = x->left;

	// A subarvore que era filha, agora é filha de h,
	// mas ela precisa saber quem é seu pai agr
	if (h->right != NULL) h->right->parent = h;

	x->left = h;

	x->parent = h->parent;
	h->parent = x;

	if (hParent != NULL) {
		if (hParent->right == h) {
			hParent->right = x;
		} else {
			hParent->left = x;
		}
	}

	x->N = h->N; 
	h->N = size(h->left) + size(h->right) + 1;
}


//All the items in S are smaller than the items in T
static Node join(Node S, Node T) {
	if (S == NULL) return T;
	if (T == NULL) return S;

	Node x = maximum(S);
	splay(x);

	x->right = T;
	T->parent = x;

	//x is the root of the joining tree
	x->N = size(x->left) + size(x->right) + 1;
	return x;
}

static Node maximum(Node x) {
	if (x->right == NULL) return x;
	return maximum(x->right);
}

static Node* split(Node x) {
	Node S, T;
	splay(x);
	T = x->right;
	if (x->right != NULL) T->parent = NULL;
	

	S = x;
	S->right = NULL;
	S->N = size(S->left) + 1;

	x = NULL;

	split_roots[0] = S;
	split_roots[1] = T;

	return split_roots;
}

static void delete(Node x) {

	Node* trees;
	trees = split(x);
	if(trees != NULL) {
		if (trees[0] != NULL) {
			//x->left->parent = x
			if (trees[0]->left != NULL) trees[0]->left->parent = NULL;
		}
		root = join(trees[0]->left, trees[1]);
		trees[0] = NULL;
		trees[1] = NULL;
	}
}

/************************   PRINT FUNCTIONS ************************/

void printTree() {
	printSPLAY(root, 1);
}


void printRoot() {
	if(root != NULL) printf("Root é: Chave: %d -- Valor: %d\n", root->key, root->val);
	else printf("Root é NULL\n");
}


static void printSPLAY(Node x, int i) {
	int pai;
	if (x != NULL) {
		printSPLAY(x->left, i+1);
		if (x->parent == NULL) pai = 0;
		else pai = x->parent->key;
		printf("%*d:%d\n", 2*i, x->val, x->N);
		printSPLAY(x->right, i+1);
	}
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
static void print2DUtil(Node x, int space, FILE *pFile)
{
	// Base case
	if (x == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(x->right, space, pFile);

	// Print current node after space
	// count
	fprintf(pFile,"\n");
	for (int i = COUNT; i < space; i++)
		fprintf(pFile," ");
	fprintf(pFile,"%d\n", x->val);

	// Process left child
	print2DUtil(x->left, space, pFile);
}

// Wrapper over print2DUtil()
void print2D(FILE *pFile)
{
	// Pass initial space count as 0
	print2DUtil(root, 0, pFile);
}