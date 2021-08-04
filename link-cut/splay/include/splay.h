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
void printTree(FILE*);
void printRoot();
void printPai();
#endif

/*
// maketree(Key)

// MakeTree
// FindRoot
// Cut  --> | rotinas auxiliares Access e Switch-Preferred-Child
// Link --> |
*/