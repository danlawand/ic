// Program to print binary tree in 2D
#include "printTree.h"
#include<stdio.h>
#include<malloc.h>
#define COUNT 10

static void  print2DUtil(Node, int, FILE*);


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
void print2D(Node root, FILE *pFile)
{
	// Pass initial space count as 0
	print2DUtil(root, 0, pFile);
}