#ifndef _BST_H
#define _BST_H
#include "node.h"

int sizeBST();
Value getBST(Key);
void putBST(Key, Value);
Key floorBST(Key);
Key ceilingBST(Key);
Key minBST();
void deleteMinBST();
void deleteBST(Key);
void printTree();
#endif