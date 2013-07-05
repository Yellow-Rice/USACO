/*
ID: philipy1
LANG: C
TASK: castle
*/
#include <stdio.h>
#include <stdlib.h>

int castle[50 * 50];
int wall[50 * 50];
int M, N, SIZE;


int find(int i);
void merge(int i, int j);

int main()
{
	unsigned i, j;
	int count = 0, max1 = 0, max2 = 0, position;
	char direction = 'C';
	
	FILE *fin = fopen("castle.in", "r");
	fscanf(fin, "%d %d", &M, &N);
	SIZE = M * N;	
	for (i = 0; i < SIZE; ++i) {
		castle[i] = -1;
	}
	for (i = 0; i < SIZE; ++i) {
		fscanf(fin, "%d", wall + i);
		if (!(1 & wall[i]) && (i % M >= 1)) {
				merge(i - 1, i);
		}
		if (!(2 & wall[i]) && (i >= M)) {
			merge(i - M, i);
		}
	}
	fclose(fin);
	
	for (i = 0; i < SIZE; ++i) {
		if (castle[i] < 0) {
			++count;
			if (castle[i] < max1)
				max1 = castle[i];
		}
		if ((2 & wall[i]) && (i >= M) && (find(i) != find(i - M)) && (castle[find(i)] + castle[find(i - M)] <= max2)) {
			if ((castle[find(i)] + castle[find(i - M)] != max2) || (i % M <= position % M)) {
				max2 = castle[find(i)] + castle[find(i - M)];
				direction = 'N';
				position = i;
			}
		}
		if ((4 & wall[i]) && (i % M < M - 1) && (find(i) != find(i + 1)) && (castle[find(i)] + castle[find(i + 1)] <= max2)) {
			if ((castle[find(i)] + castle[find(i + 1)] != max2) || ((i % M <= position % M) && (position != i))) {
				max2 = castle[find(i)] + castle[find(i + 1)];
				direction = 'E';
				position = i;
			}
		}
	}
	
	for (i = 0; i < N; ++i) {
		for (j = 0; j < M; ++j) {
			printf("%d\t", castle[i * M + j]);
		}
		printf("\n");
	}
	
	FILE *fout = fopen("castle.out", "w");
	fprintf(fout, "%d\n", count);
	fprintf(fout, "%d\n", -max1);
	fprintf(fout, "%d\n", -max2);
	fprintf(fout, "%d %d %c\n", position / M + 1, position % M + 1, direction);
	fclose(fout);
	
	exit(0);
}

int find(int i)
{
	while (castle[i] >= 0)
		i = castle[i];
	return i;
}

void merge(int i, int j)
{
	int m = find(i);
	int n = find(j);
	if (m != n) {
		castle[m] += castle[n];
		castle[n] = m;
	}
}
