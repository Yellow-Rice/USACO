/*
 ID: philipy1
 LANG: C
 TASK: preface
 */
#include <stdio.h>
#include <stdlib.h>

void initialize();

#define SIZE 3500
int N;
int I[SIZE + 1], V[SIZE + 1], X[SIZE + 1], L[SIZE + 1], C[SIZE + 1], D[SIZE + 1], M[SIZE + 1];
int count_I = 0, count_V = 0, count_X = 0, count_L = 0, count_C = 0, count_D = 0, count_M = 0;

int main()
{
	FILE *fin = fopen("preface.in", "r");
	fscanf(fin, "%d", &N);
	fclose(fin);
	
	initialize();
	
	int i;
	for (i = 1; i <= N; ++i) {
		count_I += I[i];
		count_V += V[i];
		count_X += X[i];
		count_L += L[i];
		count_C += C[i];
		count_D += D[i];
		count_M += M[i];
	}
	
	FILE *fout = fopen("preface.out", "w");
	if (count_I) {
		fprintf(fout, "I %d\n", count_I);
	}
	if (count_V) {
		fprintf(fout, "V %d\n", count_V);
	}
	if (count_X) {
		fprintf(fout, "X %d\n", count_X);
	}
	if (count_L) {
		fprintf(fout, "L %d\n", count_L);
	}
	if (count_C) {
		fprintf(fout, "C %d\n", count_C);
	}
	if (count_D) {
		fprintf(fout, "D %d\n", count_D);
	}
	if (count_M) {
		fprintf(fout, "M %d\n", count_M);
	}
	fclose(fout);

	exit(0);
}

void initialize()
{
	int i;
	for (i = 0; i <= N; ++i) {
		I[i] = 0;
		V[i] = 0;
		X[i] = 0;
		L[i] = 0;
		C[i] = 0;
		D[i] = 0;
		M[i] = 0;
	}
	I[1] = 1;
	I[2] = 2;
	I[3] = 3;
	I[4] = 1;
	V[4] = V[5] = V[6] = V[7] = V[8] = 1;
	I[6] = 1;
	I[7] = 2;
	I[8] = 3;
	I[9] = 1;
	X[9] = 1;
	X[10] = 1;
	X[20] = 2;
	X[30] = 3;
	X[40] = 1;
	L[40] = L[50] = L[60] = L[70] = L[80] = 1;
	X[60] = 1;
	X[70] = 2;
	X[80] = 3;
	X[90] = 1;
	C[90] = 1;
	C[100] = 1;
	C[200] = 2;
	C[300] = 3;
	C[400] = 1;
	D[400] = D[500] = D[600] = D[700] = D[800] = 1;
	C[600] = 1;
	C[700] = 2;
	C[800] = 3;
	C[900] = 1;
	M[900] = 1;
	M[1000] = 1;
	M[2000] = 2;
	M[3000] = 3;
	
	for (i = 11; i <= N; ++i) {
		if (i > 1000) {
			I[i] = I[i % 1000] + I[(i / 1000) * 1000];
			V[i] = V[i % 1000] + V[(i / 1000) * 1000];
			X[i] = X[i % 1000] + X[(i / 1000) * 1000];
			L[i] = L[i % 1000] + L[(i / 1000) * 1000];
			C[i] = C[i % 1000] + C[(i / 1000) * 1000];
			D[i] = D[i % 1000] + D[(i / 1000) * 1000];
			M[i] = M[i % 1000] + M[(i / 1000) * 1000];
		}
		else if (i > 100) {
			I[i] = I[i % 100] + I[(i / 100) * 100];
			V[i] = V[i % 100] + V[(i / 100) * 100];
			X[i] = X[i % 100] + X[(i / 100) * 100];
			L[i] = L[i % 100] + L[(i / 100) * 100];
			C[i] = C[i % 100] + C[(i / 100) * 100];
			D[i] = D[i % 100] + D[(i / 100) * 100];
			M[i] = M[i % 100] + M[(i / 100) * 100];
		}
		else if (i > 10) {
			I[i] = I[i % 10] + I[(i / 10) * 10];
			V[i] = V[i % 10] + V[(i / 10) * 10];
			X[i] = X[i % 10] + X[(i / 10) * 10];
			L[i] = L[i % 10] + L[(i / 10) * 10];
			C[i] = C[i % 10] + C[(i / 10) * 10];
			D[i] = D[i % 10] + D[(i / 10) * 10];
			M[i] = M[i % 10] + M[(i / 10) * 10];
		}
	}
}
