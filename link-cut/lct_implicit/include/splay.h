#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"
#include <stdio.h>

//NODE MAKESPLAY()
//VOID JOIN(NODE, )
void splay(Node);
void printSPLAY(Node, int);
Node* split(Node);
Node maximum(Node);
Node minimum(Node);
void pushBitDown(Node);
#endif
