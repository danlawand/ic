#include "lct.h"
#include <stdio.h>

static int valor;

// Funções auxiliares do access
static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

void lctInit() {
	valor = 0;
}

Node maketree() {
	// if (chave == 'Z') chave = 'a';
	return newNode(valor++, NULL, NULL, NULL, NULL, 0, 0);

}

/*  removePreferredChild(Node v)
	// Imagine que estamos enviando o node, (key = 2 e v->bit = 0), da seguinte árvore
	//    4:0
	//  2:0
	//    1:0
	// Isso significa que removeremos o node 4 da árvore, e ele terá como pathParent o node 2
	// Com resultado:
	//  2:0
	//    1:0

	// O caso com v->bit = 1 seria:
	//    1:0
	//  2:1
	//    4:0
	// Com resultado
	//    1:0
	//  2:1
*/
static void removePreferredChild(Node v) {
	if (v->children[1 - v->bit] != NULL) {
		v->children[1 - v->bit]->pathParent = v;
		v->children[1 - v->bit]->parent = NULL;
	}
	v->children[1 - v->bit] = NULL;
}

static void switchPreferredChild(Node w, Node v) {
	if (w->children[1 - w->bit] != NULL) {
		w->children[1 - w->bit]->pathParent = v;
		w->children[1 - w->bit]->parent = NULL;
	}
	w->children[1 - w->bit] = v;
	v->parent = w;
	v->pathParent = NULL;
}

// Sleator refere ao access como expose(v)
//Acessa o nó v, criando o  preferred path da raiz até o nó v
void access(Node v) {
	Node w;
	// Faz v raiz de sua splay (ou seja, filhos "esquerdos" ([bit]) são menos profundos que v)
	// e filhos "direitos" ([1-bit]) são mais profundos que v
	splay(v);

	printf("--\n");
	printSPLAY(v, 1);
	printf("--\n");

	// Remove os filhos "direitos" ([1-bit]), pois o caminho preferencial deve terminar em v,
	// que é menos profundo que seus filhos "direitos"
	removePreferredChild(v);

	// Se já não estava no caminho preferencial com a raiz da LCT (ou seja, se  e raiz da LCT não estão na mesma splay)
	// Logo, v terá um pathParent
	// Vamos para o pathParent, que está em outra splay tree -- (w = v->pathParent;)
	// Tornamos ele (w) raiz da splay tree 						 -- (splay(w);)
	// w tem filhos direitos mais profundos que ele, ou seja, tem um caminho preferencial com os filhos direitos
	// vamos retirar os filhos direitos e eles serão uma outra splay tree -- (switchPreferredChild(w, v);)
	// Estes ex-filhos direitos irão ter o pathParent para a v, (que será a raiz da splay tree que representa o referred path)
	// E w terá como novos filhos direitos a sub-árvore de v, em que não tem filhos direitos, mas pode ter filhos esquerdos
	// Após isso, fazemos o v ser a raiz da splay tree, que representa o caminho preferencial
	// E v não terá filhos direitos
	// Se houver um pathParent, repete
	// Caso contrário, estamos no caminho preferencial da raiz da LCT até v

	// Invariante: v não tem filhos direitos (1-bit)
	while (v->pathParent != NULL) {
		w = v->pathParent;
		splay(w);
		switchPreferredChild(w, v);
		splay(v);
	}
	//v é raiz da splay tree do preferred path
	// SE ADICIONAR O PUSHBITDOWN NO FINAL DO SPLAY, INVARIANTE: O BIT DE V É ZERO AO FINAL DO ACCESS
}


// v e w estão em árvores distintas e v é a raiz da sua árvore (da represented tree, não necessariamente da Splay Tree);
// junta as árvores de v e w, acrescentando a aresta v->w, fazendo w pai de v (ou v filho de w).
void link(Node v, Node w) {
	evert(v);
	access(w);
	// O ACCESS ME DARIA O BIT DE W = 0
	w->children[1 - w->bit] = v;
	v->parent = w;
}

//Modifica a LCT que contém v para que v torne-se a raiz desta LCT
// Muda a profundidade, dos vértices de v até a LCT. Para que v seja a raiz da LCT, tendo profundidade zero.
void evert(Node v) {
	access(v);
	//nó v é a raiz da LCT

	//reverte o bit
	//https://www.cs.cmu.edu/~sleator/papers/dynamic-trees.pdf
	// page 372

	// CRIAR A ROTINA INVERTE QUE INVERTE O BIT NA SPLAY
	v->bit = 1 - v->bit;
}

Node findRoot(Node v) {
	access(v);
	Node r = minimum(v);
	splay(r);
	return r;
}

//pré-condição: v não é uma raiz da lct; remove a aresta v->parent(v).
void cut(Node v) {
	if (findRoot(v) == v) return;

	//acesso v, e v se torna raiz na sua splay tree
	access(v);



	// SE FIZERMOS A ALTERAÇÃO NO SPLAY DO PUSHBITDOWN, ESSE PUSHBITDOWN SOME
	// para garantir que o bit dele vá para o filho, se for 1
	// pushBitDown(v);

	//realizo o split no pai do v, porque v->parent é menos profundo do que v, portanto v cai para o lado greater
	split(maximum(v->children[0]));
}
