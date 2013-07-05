/*
 ID: philipy1
 LANG: C
 TASK: sort3
 */
#include <stdio.h>
#include <stdlib.h>

int ONE[4] = {0, 0, 0, 0};
int TWO[4] = {0, 0, 0, 0};
int THREE[4] = {0, 0, 0, 0};
int SIZE[4] = {0, 0, 0, 0};
int DATA[1000];
int N, i, temp, switch_count = 0;

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	FILE *fin = fopen("sort3.in", "r");
	fscanf(fin, "%d", &N);
	for (i = 0; i < N; ++i) {
		fscanf(fin, "%d", &temp);
		DATA[i] = temp;
		++SIZE[temp];
	}
	fclose(fin);
	
	for (i = 0; i < SIZE[1]; ++i) {
		++ONE[DATA[i]];
	}
	for (; i < SIZE[1] + SIZE[2]; ++i) {
		++TWO[DATA[i]];
	}
	for (; i < SIZE[1] + SIZE[2] + SIZE[3]; ++i) {
		++THREE[DATA[i]];
	}
	
	switch_count = min(ONE[2], TWO[1]) + min(ONE[3], THREE[1]) + min(TWO[3], THREE[2]) + 2 * (ONE[2] > TWO[1] ? ONE[2] - TWO[1] : TWO[1] - ONE[2]);
	
	FILE *fout = fopen("sort3.out", "w");
	fprintf(fout, "%d\n", switch_count);
	//fprintf(stdout, "%d\n", switch_count);
	fclose(fout);
	
	exit(0);
}
