#ifndef _NODE_H
#define _NODE_H

#include "item.h"

typedef struct node *Node;
struct node {
	Key key;	/*key*/
	Value val;	/*associated value*/
	Node left;	/*link to subtrees*/
	Node right;
	Node parent;	
	int N;		/* # nodes in subtree rooted here*/
};

Node newNode(Key, Value, Node, Node, Node, int);

#endif