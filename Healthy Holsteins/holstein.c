/*
 ID: philipy1
 LANG: C
 TASK: holstein
 */
#include <stdio.h>
#include <stdlib.h>

void search(int start, int current_round, int total_round);
void print_ans(int round);

int V, needs[25], G, feeds[15][25];
int ans[15] = {-1}, sum[25] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
FILE *fout;

int main()
{
	int i, j;
	FILE *fin = fopen("holstein.in", "r");
	fscanf(fin, "%d", &V);
	printf("%d\n", V);
	for (i = 0; i < V; ++i) {
		fscanf(fin, "%d", needs + i);
		printf("%.4d ", *(needs + i));
	}
	printf("\n");
	fscanf(fin, "%d", &G);
	printf("%d\n", G);
	for (i = 0; i < G; ++i) {
		for (j = 0; j < V; ++j) {
			fscanf(fin, "%d", &feeds[i][j]);
			printf("%.4d ", feeds[i][j]);
		}
		printf("\n");
	}
	fclose(fin);
	
	fout = fopen("holstein.out", "w");
	for (i = 0; i < G; ++i) {
		search(0, 0, i);
	}
	
	exit(0);
}

void search(int start, int current_round, int total_round)
{
	int i, j;
	int temp;
	if (current_round < total_round) {
		for (i = start; i < G; ++i) {
			printf("current_round = %d, total_round = %d, feed[%d]\n", current_round + 1, total_round + 1, i + 1);
			for (j = 0; j < V; ++j) {
				//printf("%.4d ", feeds[i][j]);
				sum[j] += feeds[i][j];
			}
			//printf("\n");
			temp = ans[current_round];
			ans[current_round] = i;
			search(i + 1, current_round + 1, total_round);
			ans[current_round] = temp;
			for (j = 0; j < V; ++j) {
				sum[j] -= feeds[i][j];
			}
		}
	}
	else {
		for (i = start; i < G; ++i) {
			printf("current_round = %d, total_round = %d, feed[%d]\n", current_round + 1, total_round + 1, i + 1);
			for (j = 0; j < V && sum[j] + feeds[i][j] >= needs[j]; ++j) ;
			if (j == V) {
				ans[current_round] = i;
				print_ans(current_round);
			}
		}
	}
}

void print_ans(int round)
{
	int j;
	fprintf(fout, "%d", round + 1);
	printf("%d", round + 1);
	for (j = 0; j <= round; ++j) {
		fprintf(fout, " %d", ans[j] + 1);
		printf(" %d", ans[j] + 1);
	}
	fprintf(fout, "\n");
	printf("\n");
	fclose(fout);
	exit(0);
}
