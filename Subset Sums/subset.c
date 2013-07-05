/*
 ID: philipy1
 LANG: C
 TASK: subset
 */

/*
 *Basic idea:
 *C[largest, sum] = (int)(largest == sum) + C[largest - 1, sum] + C[largest - 1, sum - largest]
 */

#include <stdio.h>
#include <stdlib.h>

unsigned search(int i);
void initialize();

#define N 39
#define M (1 + 39) * 39 / 2
unsigned data[N + 1][M + 1];

int main()
{
	int size;
	FILE *fin = fopen("subset.in", "r");
	fscanf(fin, "%d", &size);
	fclose(fin);
	
	initialize();
	
	FILE *fout = fopen("subset.out", "w");
	fprintf(fout, "%u\n", search(size));
	fclose(fout);
	
	exit(0);
}

unsigned search(int i)
{
	if (i % 4 == 1 || i % 4 == 2) {
		return 0;
	}
	
	int sum = i * (i + 1) / 2;
	return data[i][sum / 2] / 2;
}

void initialize()
{
	int i, j;
	for (i = 1; i <= N; ++i) {
		data[i][1] = 1;
	}
	for (j = 2; j <= M; ++j) {
		data[1][j] = 0;
	}
	for (i = 2; i <= N; ++i) {
		for (j = 2; j <= i * (i + 1) / 2; ++j) {
			data[i][j] = data[i - 1][j] + (i == j);
			if (j > i) {
				data[i][j] += data[i - 1][j - i];
			}
		}
		for (; j <= M; ++j) {
			data[i][j] = 0;
		}
	}
}
