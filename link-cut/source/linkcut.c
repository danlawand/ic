#include "node.h"
#include "linkcut.h"
#include <stdlib.h>

static Node root; /*root of the Link-cut tree*/

void switch_path_parent(Node v, Node w) {
	if (v->right == NULL) return;
	v->right->path_parent = v;
	v->right = w;
}

//supõe que foi feito splay no v
//Return root of the link cut tree
void access(Node v) {
	Node w, h;
	switch_path_parent(v, NULL);
	//Only the root of the splay tree that contains the root of the link-cut tree has the path_parent NULL
	while (v->path_parent != NULL) {
		w = v->path_parent;
		splay(w);
		switch_path_parent(w, v);
		v->path_parent = NULL;
		v = w;
	}
	// Here v is root of the splay tree that contains the root of the link cut tree
}


// IMPLEMENTAR SPLAY TREE QUE DADO O NÓ V SOBE À RAÍZ.