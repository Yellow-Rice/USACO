/*
ID: philipy1
LANG: C
TASK: checker
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void search(int round, int size);
void print_path();

int path[13];
int count = 0;
int N;
FILE* fout;

int main()
{
	FILE *fin = fopen("checker.in", "r");
	int i, j;
	fscanf(fin, "%d", &N);
	fclose(fin);
	fout = fopen ("checker.out", "w");

	search(0, N);

	fprintf(fout, "%d\n", count);

	fclose(fout);
	exit (0);
}

void search(int round, int size)
{
	/*
	 * round:	new x
	 * i:		new y
	 * j:		existed x
	 * path[j]:	existed y related to j(existed x)
	**/
	int i, j;
	for (i = 0; i < size; ++i) {
		for (j = 0; j < round; ++j) {
			if ((i == path[j]) || \
				(round - j == i - path[j]) || \
				(round - j == path[j] - i)) {
				break;
			}
		}
		if (j == round) {
			path[round] = i;
			if (round == size - 1) {
				if (count < 3) {
					print_path();
				}
				++count;
			}
			else {
				search(round + 1, size);
			}
		}
	}
}

void print_path()
{
	int k;
	fprintf(fout, "%d", path[0]);
	for (k = 1; k < N; ++k) {
		fprintf(fout, " %d", path[k]);
	}
	fprintf(fout, "\n");
}
