#include "node.h"
#include <stdio.h>
#include <stdlib.h>

static void *mallocSafe(size_t);

Node newNode(Key key, Value val, Node left, Node right, int N) {
	Node p = mallocSafe(sizeof(*p));
	p->key = key;
	p->val = val;
	p->left = left;
	p->right = right;
	p->N = N;
	return p;
}

static void *mallocSafe(size_t nbytes) {
	void *p = malloc(nbytes);
	if (p == NULL) {
		printf("Erro: alocação de memória falhou no módulo node.\n");
		exit(0);
	}
	return p;
}
