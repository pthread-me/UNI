#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void setup(char *filename);
int rank1(int i);
int rank(char c, int i);
int count(char *query);

char *bitvector;
uint16_t *miniheaders;
uint64_t *macroheaders;
int dollarPos;
int countAs;
uint64_t masks[64];

void main(int argc, char *argv[]) {

	bitvector = (char *) malloc(1000000 / 8);
	miniheaders = (uint16_t *) malloc(1000000 / 32);
	macroheaders = (uint64_t *) malloc((1065535 / 65536) * 8);

	setup(argv[1]);

	char query[101];

	while (scanf("%100s", &query) == 1) {
		printf("%i occurrences of %s.\n", count(query), query);
	}

	return;
}

void setup(char *filename) {

	FILE *file = fopen(filename, "r");

	int currentRank = 0;

	memset(bitvector, 0, 1000000 / 8);
	int miniRank = 0;

	for (int i = 0; i < 1000000; i++) {

		if (i % 64 == 0) {
			miniheaders[i/64] = (uint16_t) miniRank;
		}

		if (i % 65536 == 0) {
			miniRank = 0;
			macroheaders[i / 65536] = (uint64_t) currentRank;
		}

		char c = (char) fgetc(file);

		if (c == 'B') {
			currentRank++;

			bitvector[i / 8] = bitvector[i / 8] | (1 << i % 8);
			miniRank++;
		}

		if (c == '$') {
			dollarPos = i;
		}
	}

	fclose(file);

	memset(&masks[63], 255, 8);

	for (int i = 62; i >= 0; i--) {
		memcpy(&masks[i], &masks[i + 1], 8);
		char * charMask = (char *) &masks[i];
		charMask[(i + 1) / 8] = charMask[(i + 1) / 8] & ~(1 << (i + 1) % 8);
	}

	countAs = rank('A', 999999);

	return;
}

int rank1(int i) {

	int sum = (int) miniheaders[i / 64] + (int) macroheaders[i / 65536];

	uint64_t miniblock = *(uint64_t *) &bitvector[(i / 64) * 8];

	miniblock = miniblock & masks[i % 64];

	sum += __builtin_popcountll(miniblock);

	return(sum);
}

int rank(char c, int i) {

	if (i < 0) {
		return(0);
	}

	int rank1i = rank1(i);

	if (c == 'A') {
		if (i >= dollarPos) {
			return((i + 1) - rank1i - 1);
		} else {
			return((i + 1) - rank1i);
		}
	} else {
		return(rank1i);
	}
}

int count(char *query) {

	int m = strlen(query);

	int s = 0;
	int e = 999999;

	for (int i = m - 1; i >= 0 && s <= e; i--) {

		if (query[i] == 'A') {
			s = rank('A', s - 1) + 1;
			e = rank('A', e);
		} else {
			s = countAs + rank('B', s - 1) + 1;
			e = countAs + rank('B', e);
		}
	}

	return(e - s + 1);
}
