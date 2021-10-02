#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"
#include <stdio.h>

typedef struct splayRoots *SplayRoots;
struct splayRoots {
	SplayRoots next;
	Node root;
};

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

void initSplay(int);

SplayRoots newSplayTree(Node, SplayRoots);

Node maketree();
//:  cria uma nova árvore, enraizada em um novo nó, e a devolve (devolve o endereço do novo nó, que é a raiz da árvore);

void link(Node, Node);
//: pré-condição: u e v estão em árvores distintas e v é a raiz da sua árvore; junta as árvores de u e v, acrescentando a aresta v->u. 

void cut(Node);
//: pré-condição: v não é uma raiz de árvore; remove a aresta v->parent(v). 


Node findroot(Node);
//: devolve a raiz da árvore que contém v.

void evert(Node);
//: modifica a árvore que contém v para que v torne-se a raiz desta árvore (reverte as arestas no caminho de v até a raiz da sua árvore). 


#endif

/*
// maketree(Key)

// MakeTree
// FindRoot
// Cut  --> | rotinas auxiliares Access e Switch-Preferred-Child
// Link --> |
*/