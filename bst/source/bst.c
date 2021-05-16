#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

static Node root; /*root of BST*/

static Node put(Node, Key, Value);
static Value get(Node, Key);
static int size(Node);
static Node min(Node); 
static Node floorTree(Node, Key);
static Node ceiling(Node, Key);
static Node deleteMin(Node);
static Node delete(Node, Key);
static void printBST(Node, int);


int sizeBST() {
	return size(root);
}

static int size(Node x) {
	if (x == NULL) return 0;
	return x->N;
}


Value getBST(Key key) {
	return 	get(root, key);
}

static Value get(Node x, Key key) {
	if (x == NULL) return NULL;
	int cmp = compareKeys(key, x->key);
	if (cmp < 0) return get(x->left, key);
	else if (cmp > 0) return get(x->right, key);
	else return x->val;
}


void putBST(Key key, Value val) {
	root = put(root, key, val);
	//root = splay(root,key)
}

static Node put(Node x, Key key, Value val) {
	if(x == NULL) return newNode(key, val, NULL, NULL, 1);
	int cmp = compareKeys(key, x->key);
	if (cmp < 0) x->left = put(x->left, key, val);
	else if (cmp > 0) x->right = put(x->right, key, val);
	else x->val = val;
	x->N = size(x->left) + size(x->right) + 1;
	return x;
}

Key floorTreeBST(Key key) {
	Node x = floorTree(root, key);
	if (x == NULL) return NULL;
	return x->key;
}

static Node floorTree(Node x, Key key) {
	if (x == NULL) return NULL;
	int cmp = compareKeys(key, x->key);
	if (cmp == 0) return x;
	if (cmp < 0) return floorTree(x->left, key);
	Node t = floorTree(x->right, key);
	if (t != NULL) return t;
	else return x;
}

Key ceilingBST(Key key) {
	Node x = ceiling(root, key);
	if (x == NULL) return NULL;
	return x->key;
}

static Node ceiling(Node x, Key key) {
	if (x == NULL) return NULL;
	int cmp = compareKeys(key, x->key);
	if (cmp == 0) return x;
	if (cmp > 0) return ceiling(x->right, key);
	Node t = ceiling(x->left, key);
	if (t != NULL) return t;
	else return x;
}

Key minBST() {
	if (root == NULL) return NULL;
	return min(root)->key;
}

static Node min(Node x) {
	if (x->left == NULL) return x;
	return min(x->left);
}


void deleteMinBST() {
	root = deleteMin(root);
}

//Não entendi como o coletor de lixo entra em ação
static Node deleteMin(Node x) {
	if (x == NULL) return NULL;
	if (x->left == NULL) return x->right;
	x->left = deleteMin(x->left);
	x->N = size(x->left) + size(x->right) + 1;
	return x;
}



void deleteBST(Key key) {
	root = delete(root, key);
	printf("Remocao completa da chave: %d\n", key);
}

static Node delete(Node x, Key key){
	if (x == NULL) return NULL;
	int cmp = compareKeys(key, x->key);
	if (cmp < 0) x->left = delete(x->left, key);
	else if (cmp > 0) x->right = delete(x->right, key);
	else {
		if(x->right == NULL) return x->left;
		if(x->left == NULL) return x->right;
		Node t = x;
		x = min(t->right);
		x->right = deleteMin(t->right);
		x->left = t->left;
	}
	x->N = size(x->left) + size(x->right) + 1;
	return x;
}

void printTree() {
	printBST(root, 1);
}

static void printBST(Node x, int i) {
	if (x != NULL) {
		printBST(x->left, i+1);
		printf("%*d\n", 2*i, x->val);
		printBST(x->right, i+1);
	}
}