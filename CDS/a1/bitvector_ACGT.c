#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void setup(char *filename);
int rank1(int i, int alphabet_index);
int rank(char c, int i);
int count(char *query);

char** Bitvectors;
uint16_t** Mini;
uint64_t** Macro;
int dollarPos;

int* countAs;
uint64_t masks[64];

void main(int argc, char *argv[]) {

	Bitvectors = calloc(4, sizeof(char*));
	Mini = calloc(4, sizeof(uint16_t*));
	Macro = calloc(4, sizeof(uint64_t*));
	countAs = calloc(4, sizeof(int));

	for(int i=0; i<4; i++){
		Bitvectors[i] = (char *) malloc(1000000 / 8);
		Mini[i] = (uint16_t *) malloc(1000000 / 32);
		Macro[i] = (uint64_t *) malloc((1065535 / 65536) * 8);
		
		memset(Bitvectors[i], 0, 1000000 / 8);
	}

	setup(argv[1]);

	char query[101];

	while (scanf("%100s", &query) == 1) {
		printf("%i occurrences of %s.\n", count(query), query);
	}

	return;
}

void setup(char *filename) {

	FILE *file = fopen(filename, "r");
	
	//im pretty sure calloc initializes the heap block as all 0's, but just to 
	//be safe
	int* currentRank = calloc(4, sizeof(int));
	for(int i=0; i<4; i++){
		currentRank[i] = 0;
	}

	int* miniRank = calloc(4, sizeof(int));


	for (int i = 0; i < 1000000; i++) {

		if (i % 64 == 0) {
			Mini[0][i / 64] = (uint16_t) miniRank[0];
			Mini[1][i / 64] = (uint16_t) miniRank[1];
			Mini[2][i / 64] = (uint16_t) miniRank[2];
			Mini[3][i / 64] = (uint16_t) miniRank[3];
		}

		if (i % 65536 == 0) {
			miniRank[0] = 0;
			miniRank[1] = 0;
			miniRank[2] = 0;
			miniRank[3] = 0;

			Macro[0][i / 65536] = (uint64_t) currentRank[0];
			Macro[1][i / 65536] = (uint64_t) currentRank[1];
			Macro[2][i / 65536] = (uint64_t) currentRank[2];
			Macro[3][i / 65536] = (uint64_t) currentRank[3];
		}

		char c = (char) fgetc(file);

		if (c == 'A') {
			countAs[0] = countAs[0] +1;
			currentRank[0] = currentRank[0] + 1;
			Bitvectors[0][i / 8] = Bitvectors[0][i / 8] | (1 << i % 8);
			miniRank[0] = miniRank[0] +1;
		}else if(c == 'C') {
			countAs[1] = countAs[1] +1;
			currentRank[1] = currentRank[1] + 1;
			Bitvectors[1][i / 8] = Bitvectors[1][i / 8] | (1 << i % 8);
			miniRank[1] = miniRank[1] +1;
		}else if(c == 'G') {
			countAs[2] = countAs[2] +1;
			currentRank[2] = currentRank[2] + 1;
			Bitvectors[2][i / 8] = Bitvectors[2][i / 8] | (1 << i % 8);
			miniRank[2] = miniRank[2] +1;
		}else if (c == 'T') {
			countAs[3] = countAs[3] +1;
			currentRank[3] = currentRank[3] + 1;
			Bitvectors[3][i / 8] = Bitvectors[3][i / 8] | (1 << i % 8);
			miniRank[3] = miniRank[3] +1;
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


	return;
}

int rank1(int i, int alphabet_index) {

	int sum = (int) Mini[alphabet_index][i / 64] + 
		(int) Macro[alphabet_index][i / 65536];

	uint64_t miniblock = *(uint64_t *) &Bitvectors[alphabet_index][(i / 64) * 8];

	miniblock = miniblock & masks[i % 64];

	sum += __builtin_popcountll(miniblock);

	return(sum);
}

int rank(char c, int i) {

	if (i < 0) {
		return(0);
	}


	if (c == 'A') {
		return rank1(i, 0);
	}else if (c == 'C') {
		return rank1(i, 1);
	}else if(c == 'G'){
		return rank1(i, 2);
	}else if(c == 'T'){
		return rank1(i, 3);
	}
}

int count(char *query) {

	int m = strlen(query);

	int s = 0;
	int e = 999999;

	for (int i = m - 1; i >= 0 && s <= e; i--) {

		char c = query[i];

		if (c == 'A') {
			s = rank('A', s - 1) + 1;
			e = rank('A', e);
		}else if(c == 'C'){
			s = countAs[0] + rank('C', s - 1) + 1;
			e = countAs[0] + rank('C', e);
		}else if(c == 'G'){
			s = countAs[0] + countAs[1] + rank('G', s - 1) + 1;
			e = countAs[0] +countAs[1] + rank('G', e);
		}else if(c == 'T'){
			s = countAs[0] + countAs[1] + countAs[2] + rank('T', s - 1) + 1;
			e = countAs[0] + countAs[1] + countAs[2]+ rank('T', e);
		}
	}

	return(e - s + 1);
}
