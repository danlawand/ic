#ifndef _NODE_H
#define _NODE_H

#include "item.h"

typedef struct node *Node;
struct node {
	Key key;	/*key*/
	Value val;	/*associated value*/
	Node children[2]; /*link to subtrees*/
	// Node left;
	// Node right;
	Node parent;
	Node pathParent;
	int bit;
	int N;		/* # nodes in subtree rooted here*/
};

Node newNode(Key, Value, Node, Node, Node, Node, int, int);

#endif