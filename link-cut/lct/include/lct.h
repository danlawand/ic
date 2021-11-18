#ifndef _LCT_H
#define _LCT_H
#include "splay.h"
#include <stdio.h>

void lctInit();

//:  cria uma nova árvore, enraizada em um novo nó, e a devolve (devolve o endereço do novo nó, que é a raiz da árvore);
Node maketree();

//: pré-condição: u e v estão em árvores distintas e v é a raiz da sua árvore; junta as árvores de u e v, acrescentando a aresta v->u. 
void link(Node, Node);


void access(Node);


//: pré-condição: v não é uma raiz de árvore; remove a aresta v->parent(v). 
// void cut(Node);


//: devolve a raiz da árvore que contém v.
Node findRoot(Node);


//Operação: Enraiza a árvore que contém o nó v no próprio nó v
void evert(Node);

/************ROTINAS AUXILIARES***************/

//Funções que identificam o filho (direito ou esquerdo), o pai ou o pathparent
void quemEhDireito(Node);
void quemEhEsquerdo(Node);
void quemEhPai(Node);
void quemEhPathParent(Node);

// Analisa a splay do node x, buscando sua raiz e imprimindo toda a splay
void analisaSplay(Node);

//Analisa o nó e imprime seu comportamento 
void analisaNode(Node);

//Analisa o nó e imprime seu comportamento em um arquivo
void analisa_Node_E_Imprime_em_arquivo(Node, FILE*);

#endif