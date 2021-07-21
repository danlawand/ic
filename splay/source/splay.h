#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"
#include <stdio.h>

typedef struct splayRoots *SplayRoots;
struct splayRoots {
	SplayRoots next;
	Node root;
};


int initSplay();
void splay(Node);
Value getSPLAY(Key);
void putSPLAY(Key, Value);
void deleteSPLAY(Key);
int sizeSPLAY();
Key maxSPLAY();
int isRoot(Node);
/**** PRINT ****/
void printTree();
void printRoot();
void print2D(FILE*);
void printPai();
#endif


// FindRoot
// Cut
// Link
// path_aggregate	