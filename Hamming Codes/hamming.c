/*
 ID: philipy1
 LANG: C
 TASK: hamming
 */

#include <stdio.h>
#include <stdlib.h>

int hamming_distance(int m, int n);
int count_one(int n);

int N, B, D;
int ans[64] = {0}, size = 1, count = 1;

int main()
{
	FILE *fin = fopen("hamming.in", "r");
	fscanf(fin, "%d %d %d", &N, &B, &D);
	fclose(fin);
	
	int i, j;
	
	while (size < N) {
		for (i = 0; i < size && hamming_distance(ans[i], count) >= D; ++i) ;
		if (i == size) {
			ans[size++] = count;
		}
		++count;
	}
	
	FILE *fout = fopen("hamming.out", "w");
	for (i = 0; i < size; ++i) {
		fprintf(fout, "%d", ans[i]);
		if (i % 10 != 9 && i != size - 1) {
			fprintf(fout, " ");
		}
		else {
			fprintf(fout, "\n");
		}
	}
	fclose(fout);
	
	exit(0);
}

int hamming_distance(int m, int n)
{
	int temp = m ^ n; //^ means XOR
	int count = 0;
	while (temp) {
		if (temp % 2) {
			++count;
		}
		temp >>= 1;
	}
	return count;
}
