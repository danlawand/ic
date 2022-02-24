#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"
#include <stdio.h>

void splayInit();
Node makeSplay();
void join(Node, Node);
void splay(Node);
void printSPLAY(Node, int);
Node* split(Node);
Node casquinhaMax(Node);
Node casquinhaMin(Node);
void reflectBit(Node);
void pushBitDown(Node);

// Operação dumb Serve apenas para o print
Node minimumSemMudanca(Node);
#endif
