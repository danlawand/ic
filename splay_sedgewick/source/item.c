#include "item.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int compareKeys(Key k1, Key k2) {
	return k1 - k2;
}

void printValue(Value val) {
	if (val == -1) {
		printf("Valor Nulo\n");
		return;
	}
	printf("O Valor é %d\n", val);
}

int keyNull() {
	return -1;
}

int valueNull() {
	return INT_MIN;
}