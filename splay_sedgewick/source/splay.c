#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

#define COUNT 10

static Node root; /*root of Splay Tree*/
static int size(Node);
static Node splay(Node, Key);
static Node rotateRight(Node);
static Node rotateLeft(Node);
static void printSPLAY(Node, int);
static void print2DUtil(Node, int, FILE*);


int sizeSPLAY() {
	return size(root);
}

static int size(Node x) {
	if (x == NULL) return 0;
	return x->N;
}


Value get(Key key) {
	if (root == NULL) return valueNull();
	root = splay(root, key);
	int cmp = compareKeys(key, root->key);
	if (cmp == 0) return root->val;
	else return valueNull();
}


void put(Key key, Value val) {
	if (root == NULL) {
		root = newNode(key, val, NULL, NULL, 1); 
		return;
	}

	root = splay(root,key);

	int cmp = compareKeys(key, root->key);

	/*Insert New Node at root*/
	if (cmp < 0) {
		Node n = newNode(key, val, NULL, NULL, 1);
		n->left = root->left;
		n->right = root;
		root->left = NULL;
		root->N = size(root->left) + size(root->right) + 1;
		root = n;
	}
	/*Insert New Node at root*/
	else if (cmp > 0) {
		Node n = newNode(key, val, NULL, NULL, 1);
		n->right = root->right;
		n->left = root;
		root->right = NULL;
		root->N = size(root->left) + size(root->right) + 1;
		root = n;
	}
	/*Update the value's node*/
	else root->val = val;
	root->N = size(root->left) + size(root->right) + 1;
}

void delete(Key key) {
	if (root == NULL) return;

	root = splay(root, key);

	int cmp = compareKeys(key, root->key);

	if (cmp == 0) {
		if (root->left == NULL) {
			root = root->right;
		}
		else {
			Node x = root->right;
			root = root->left;
			root = splay(root, key);
			root->right = x;
		}
	}

	root->N = size(root->left) + size(root->right) + 1;

	printf("Remocao completa da chave: %d\n", key);
}

static Node splay (Node h, Key key) {
	if (h == NULL) return NULL;

	int cmp1 = compareKeys(key, h->key);
	/*Key in the left subtree*/
	if (cmp1 < 0) {
		/*key not in tree*/
		if (h->left == NULL) return h;
	
		int cmp2 = compareKeys(key, h->left->key);
		if (cmp2 < 0) {
			h->left->left = splay(h->left->left, key);
			h = rotateRight(h);
		} else if (cmp2 > 0) {
			h->left->right = splay(h->left->right, key);
			if (h->left->right != NULL) {
				h->left = rotateLeft(h->left);
			}
		}

		if (h->left == NULL) return h;
		else return rotateRight(h);

	/*Key in the right subtree*/
	} else if (cmp1 > 0) {
		/*Key not in tree*/
		if (h->right == NULL) return h;
		
		int cmp2 = compareKeys(key, h->right->key);
		if (cmp2 < 0) {
			h->right->left = splay(h->right->left, key);
			if (h->right->left != NULL) {
				h->right = rotateRight(h->right);
			}
		} else if (cmp2 > 0) {
			h->right->right = splay(h->right->right, key);
			h = rotateLeft(h);
		}
		if (h->right == NULL) return h;
		else return rotateLeft(h);
	}
	else {
		return h;
	}
}

static Node rotateRight (Node h) {
	Node x = h->left;
	h->left = x->right;
	x->right = h;
	x->N = h->N; 
	h->N = size(h->left) + size(h->right) + 1;
	return x;
}

static Node rotateLeft (Node h) {
	Node x = h->right;
	h->right = x->left;
	x->left = h;
	x->N = h->N; 
	h->N = size(h->left) + size(h->right) + 1;
	return x;
}



void printTree() {
	printSPLAY(root, 1);
}

static void printSPLAY(Node x, int i) {
	if (x != NULL) {
		printSPLAY(x->left, i+1);
		printf("%*d:%d\n", 2*i, x->val, x->N);
		printSPLAY(x->right, i+1);
	}
}

void printRoot() {
	printf("Root é: Chave: %d -- Valor: %d\n", root->key, root->val);
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