#ifndef _ANALISALCT_H
#define _ANALISALCT_H

#include "lct.h"
#include <stdio.h>

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