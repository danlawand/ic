#ifndef _ANALISALCT_H
#define _ANALISALCT_H

#include "lct.h"
#include <stdio.h>

//Funções que identificam o filho (direito ou esquerdo), o pai ou o pathparent
void quemEhDireito(Node, FILE*);
void quemEhEsquerdo(Node, FILE*);
void quemEhPai(Node, FILE*);
void quemEhPathParent(Node, FILE*);

// Analisa a splay do node x, buscando sua raiz e imprimindo toda a splay
void analisaSplay(Node);

//Analisa o nó e imprime seu comportamento
// FILE* pode ser NULL
void analisaNode(Node, FILE*);

//Analisa o nó e imprime seu comportamento em um arquivo
void analisa_Node_E_Imprime_em_arquivo(Node, FILE**);

#endif