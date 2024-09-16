#include <stdio.h>
#include "mtwister.h"

void main() {

	MTRand mtx = seedRand(2024);

	for (int i = 0; i < 999999; i++) {
		double x = genRand(&mtx);
		if (x < 0.25) {
			putchar('A');
		} else if (x < 0.5) {
			putchar('C');
		} else if (x < 0.75) {
			putchar('G');
		} else {
			putchar('T');
		}
	}

	putchar('$');
	return;
}