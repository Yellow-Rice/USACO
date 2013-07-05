/*
 ID: philipy1
 LANG: C
 TASK: lamps
 */
#include <stdio.h>
#include <stdlib.h>

void initialize();

int N, C;
int partial_final_state[100];
int all_state[16][100];
int min[16] = {0, 1 ,1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
_Bool ans[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main()
{
	
	FILE *fin = fopen("lamps.in", "r");
	int i, j, temp;
	_Bool flag = 0;
	fscanf(fin, "%d%d", &N, &C);
	for (i = 0; i < N; ++i) {
		partial_final_state[i] = -1;
	}
	fscanf(fin, "%d", &temp);
	while (temp != -1) {
		partial_final_state[temp - 1] = 1;
		fscanf(fin, "%d", &temp);
	}
	fscanf(fin, "%d", &temp);
	while (temp != -1) {
		partial_final_state[temp - 1] = 0;
		fscanf(fin, "%d", &temp);
	}
	fclose(fin);
	
	initialize();
	
	for (i = 0; i < 16; ++i) {
		if (min[i] <= C && (C - min[i]) % 2 == 0) {
			for (j = 0; j < N; ++j) {
				if (partial_final_state[j] == 1 - all_state[i][j]) {
					break;
				}
			}
			if (j == N) {
				flag = 1;
				ans[i] = 1;
				ans[(i / 8) * 8 + 7 - i % 8] = 1;
			}
		}
	}
	printf("%d\n", flag);
	
	FILE *fout = fopen("lamps.out", "w");
	if (!flag) {
		fprintf(fout, "IMPOSSIBLE\n");
	}
	else {
		if (ans[1]) {
			for (i = 0; i < N; ++i) {
				fprintf(fout, "%d", all_state[1][i]);
			}
			fprintf(fout, "\n");
		}
		if (ans[12]) {
			for (i = 0; i < N; ++i) {
				fprintf(fout, "%d", all_state[12][i]);
			}
			fprintf(fout, "\n");
		}
		if (ans[2]) {
			for (i = 0; i < N; ++i) {
				fprintf(fout, "%d", all_state[2][i]);
			}
			fprintf(fout, "\n");
		}
		if (ans[8]) {
			for (i = 0; i < N; ++i) {
				fprintf(fout, "%d", all_state[8][i]);
			}
			fprintf(fout, "\n");
		}
		if (ans[9]) {
			for (i = 0; i < N; ++i) {
				fprintf(fout, "%d", all_state[9][i]);
			}
			fprintf(fout, "\n");
		}
		if (ans[4]) {
			for (i = 0; i < N; ++i) {
				fprintf(fout, "%d", all_state[4][i]);
			}
			fprintf(fout, "\n");
		}
		if (ans[10]) {
			for (i = 0; i < N; ++i) {
				fprintf(fout, "%d", all_state[10][i]);
			}
			fprintf(fout, "\n");
		}
		if (ans[0]) {
			for (i = 0; i < N; ++i) {
				fprintf(fout, "%d", all_state[0][i]);
			}
			fprintf(fout, "\n");
		}
	}
	fclose(fout);
	
	exit(0);
}

void initialize()
{
	int i, j;
	for (i = 0; i < N; ++i) {
		all_state[0][i] = 1;
	}
		
	for (i = 0; i < N; ++i) {
		all_state[1][i] = 0;
	}
	
	for (i = 0; i < N; ++i) {
		all_state[2][i] = i % 2;
	}
	
	for (i = 0; i < N; ++i) {
		all_state[4][i] = 1 - (i % 2);
	}
	
	for (i = 0; i < N; ++i) {
		all_state[8][i] = (i % 3 != 0);
	}
	
	for (i = 3; i < 16; ++i) {
		if (i > 8) {
			for (j = 0; j < N; ++j) {
				all_state[i][j] = (all_state[8][j] == all_state[i - 8][j]);
			}
		}
		else if (i > 4 && i < 8) {
			for (j = 0; j < N; ++j) {
				all_state[i][j] = (all_state[4][j] == all_state[i - 4][j]);
			}
		}
		else if (i == 3) {
			for (j = 0; j < N; ++j) {
				all_state[3][j] = (all_state[2][j] == all_state[1][j]);
			}
		}
	}
}