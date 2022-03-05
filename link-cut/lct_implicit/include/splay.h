#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"
#include <stdio.h>

void splayInit();
Node makeSplay();
void join(Node, Node);
void splay(Node);
void split(Node);
Node maxSplay(Node);
Node minSplay(Node);
void reflectTree(Node);


void printSPLAY(Node, int);
// Operação dumb Serve apenas para o print
Node minimumSemMudanca(Node);
#endif
