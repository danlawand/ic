#ifndef _SPLAY_H
#define _SPLAY_H
#include "node.h"
#include <stdio.h>

// A Link-Cut Tree usa o splay.
// Node splay (Node, Key);
int sizeSPLAY();
Value get(Key);
void put(Key, Value);
void delete(Key);
void printTree();
void printRoot();
void print2D(FILE*);
#endif


// FindRoot
// Cut
// Link
// path_aggregate	