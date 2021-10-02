#ifndef _LCT_H
#define _LCT_H
#include "splay.h"
#include <stdio.h>

void lctInit();

Node maketree();
//:  cria uma nova árvore, enraizada em um novo nó, e a devolve (devolve o endereço do novo nó, que é a raiz da árvore);

void link(Node, Node);
//: pré-condição: u e v estão em árvores distintas e v é a raiz da sua árvore; junta as árvores de u e v, acrescentando a aresta v->u. 

void access(Node);
// void cut(Node);
//: pré-condição: v não é uma raiz de árvore; remove a aresta v->parent(v). 


// Node findroot(Node);
//: devolve a raiz da árvore que contém v.




/************ROTINAS AUXILIARES***************/
void printSPLAY(Node, int);
void quemEhDireito(Node);
void quemEhEsquerdo(Node);
void quemEhPai(Node);
void quemEhPathParent(Node);
void analisaSplay(Node);
void analisaNode(Node);
#endif