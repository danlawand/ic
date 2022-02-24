#include "lct.h"
#include <stdio.h>

// Funções auxiliares do access
static void removePreferredChild(Node);
static void switchPreferredChild(Node, Node);

void lctInit() {
	splayInit();
}

Node maketree() {
	return makeSplay();
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
// É chamado depois de access(v), ou seja, v->bit = 0
static void removePreferredChild(Node v) {
	/*/ Imaginando que:
	//		v
	//		 \
	//		  w
	*/
	if (v->children[1] != NULL) {
		// Tô falando que o w terá pathParent para v???
		v->children[1]->pathParent = v;
		v->children[1]->parent = NULL;
	}
	v->children[1] = NULL;
}
// É chamado depois de access(w), ou seja, w->bit = 0
static void switchPreferredChild(Node w, Node v) {
	if (w->children[1] != NULL) {
		w->children[1]->pathParent = v;
		w->children[1]->parent = NULL;
	}
	join(v, w);
	// equivale a:
	// w->children[1] = v;
	// v->parent = w;
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


// v e w estão em árvores distintas
// junta as árvores de v e w, acrescentando a aresta v->w, Fazendo v filho direito de w na splay tree (auxiliary tree) -- v é mais profundo do que w, logo v é pai de w na LCT (represented tree)
void link(Node v, Node w) {
	// V SE TORNA RAIZ DA LCT ao qual faz parte
	evert(v);

	access(w);
	// O ACCESS ME DARIA O BIT DE W = 0

	// Faça v filho direito de w na splay tree (auxiliary tree) -- v é mais profundo do que w, logo v é pai de w na represented tree (lct)
	join(v, w);
	// equivale a:
	// w->children[1] = v;
	// v->parent = w;
}


// DESSE MODO O EVERT SÓ MUDA O NODE V COMO SENDO HEAD
//Modifica a LCT que contém v para que v torne-se a raiz desta LCT
// Muda a profundidade, dos vértices de v até a LCT. Para que v seja a raiz da LCT, tendo profundidade zero.
void evert(Node v) {
	// Com access ele se torna raiz da splay tree
	access(v);
	// O que torna possível alterar os bits

	//reverte o bit
	//https://www.cs.cmu.edu/~sleator/papers/dynamic-trees.pdf
	// page 372

	// ROTINA INVERTE QUE INVERTE O BIT NA SPLAY
	reflectBit(v);
}

Node findRootSemAccess(Node v) {
	Node m = minimumSemMudanca(v);
	return m;
}

Node findRoot(Node v) {
	access(v);
	Node m = casquinhaMin(v);
	return m;
}

//pré-condição: v não é uma raiz da lct; remove a aresta de v com seu pai naLCT
void cut(Node v) {
	//acesso v, e v se torna raiz na sua splay tree
	// Quando eu dou access em v, eu tenho a garantia de que o filho direito de v é NULL na splay tree
	access(v);

	//realizo o split no pai do v, porque o pai de v é menos profundo do que v, portanto v cai para o lado greater
	Node m = casquinhaMax(v->children[0]);
	split(m);
	// split(maximum(v->children[0]));
}
