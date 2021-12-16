#ifndef _LCT_H
#define _LCT_H
#include "splay.h"
#include <stdio.h>

void lctInit();

//Operação:  cria uma nova árvore, enraizada em um novo nó, e a devolve (devolve o endereço do novo nó, que é a raiz da árvore);
Node maketree();

//pré-condição: v e w estão em árvores distintas e v é a raiz da sua árvore;
//Operação: junta as árvores de v e w, acrescentando a aresta v->w (w filho de v).
//link(v, w)
void link(Node, Node);

// Sleator refere ao access como expose(v)
//Acessa o nó v, criando o  preferred path da raiz até o nó v
void access(Node);


//Operação: devolve a raiz da árvore que contém v.
Node findRoot(Node);


//Operação: Enraiza a árvore que contém o nó v no próprio nó v
void evert(Node);


//pré-condição: v não é uma raiz de árvore; remove a aresta v->parent(v). 
//cut(v)
void cut(Node);


#endif
