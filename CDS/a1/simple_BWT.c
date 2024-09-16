#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char T[1000000];

int suffixCmp(const void *a, const void *b) {
	return(strcmp(&T[*(int *) a], &T[*(int *) b]));
}

void main() {
	int SA[1000000];

	for (int i = 0; i < 1000000; i++) {
		T[i] = (char) getchar();
		SA[i] = i;
	}

	qsort(SA, 1000000, sizeof(int), suffixCmp);

	for (int i = 0; i < 1000000; i++) {
		putchar(T[(SA[i] + 999999) % 1000000]);
	}

	return;
}