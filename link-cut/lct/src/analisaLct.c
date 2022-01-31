#include "analisaLct.h"
#include <stdio.h>

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay
static void analisaPreOrdemSplay(Node x);

void quemEhDireito(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->children[1 - x->bit] == NULL) {
			fprintf(fp, "%d Right Eh null\n",x->key);
		} else {
			fprintf(fp, "%d Right %d\n",x->key, x->children[1 - x->bit]->key);
		}
	}

	if(x->children[1 - x->bit] == NULL) {
		printf("%d Right Eh null\n",x->key);
	} else {
		printf("%d Right %d\n",x->key, x->children[1 - x->bit]->key);
	}
}

void quemEhEsquerdo(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->children[x->bit] == NULL) {
			fprintf(fp, "%d Left Eh null\n",x->key);
		} else {
			fprintf(fp, "%d Left %d\n",x->key, x->children[x->bit]->key);
		}
	}

	if(x->children[x->bit] == NULL) {
		printf("%d Left Eh null\n",x->key);
	} else {
		printf("%d Left %d\n",x->key, x->children[x->bit]->key);
	}
}

void quemEhPai(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->parent == NULL) {
			fprintf(fp, "%d parent Eh null\n",x->key);
		} else {
			fprintf(fp, "%d parent %d\n",x->key, x->parent->key);
		}
	}

	if(x->parent == NULL) {
		printf("%d parent Eh null\n",x->key);
	} else {
		printf("%d parent %d\n",x->key, x->parent->key);
	}
}

void quemEhPathParent(Node x, FILE* fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		if(x->pathParent == NULL) {
			fprintf(fp, "%d pathParent Eh null\n",x->key);
		} else {
			fprintf(fp, "%d pathParent %d\n",x->key, x->pathParent->key);
		}
	}

	if(x->pathParent == NULL) {
		printf("%d pathParent Eh null\n",x->key);
	} else {
		printf("%d pathParent %d\n",x->key, x->pathParent->key);
	}
}

void qualBit(Node x, FILE *fp) {
	if (x == NULL) return;

	if (fp != NULL) {
		fprintf(fp, "%d bit %d\n",x->key, x->bit);
	}
	printf("%d bit %d\n",x->key, x->bit);
}

// Descreve o nó, com a opção de imprimir em um arquivo
void analisaNode(Node x, FILE* fp) {
	if (x == NULL) return;

	printf("Sobre o %d\n", x->key);
	if (fp != NULL) {
		fprintf(fp, "Sobre o %d\n", x->key);
	}
	quemEhDireito(x, fp);
	quemEhEsquerdo(x, fp);
	quemEhPai(x, fp);
	quemEhPathParent(x, fp);
	qualBit(x, fp);

	if (fp != NULL) {
		fprintf(fp, "\n");
	}
	printf("\n");
	if (x->parent == NULL) {
		printSPLAY(x, 1);
		printf("\n");
	}
}

void analisaSplay(Node x) {
	if (x == NULL) return;
	if (x->parent != NULL) x = findRoot(x);
	analisaPreOrdemSplay(x);
}

// função auxiliar de 'analisaSplay', para analisar em pre-ordem a splay
static void analisaPreOrdemSplay(Node x) {
	if (x == NULL) return;
	analisaNode(x, NULL);
	analisaPreOrdemSplay(x->children[1-x->bit]);
	analisaPreOrdemSplay(x->children[x->bit]);
}
