#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"
#include <stdio.h>


void splay(Node);
void revertSPLAY();
int isRoot(Node);
void printSPLAY(Node, int);
Node minimum(Node);
Node* split(Node);
Node maximum(Node);
void pushBitDown(Node); 
#endif
