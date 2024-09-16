#include <stdio.h>
#include "mtwister.h"

void main() {

	MTRand mtx = seedRand(2024);

	for (int i = 0; i < 999999; i++) {
		putchar(genRand(&mtx) < 0.5 ? 'A' : 'B');
	}

	putchar('$');
	return;
}