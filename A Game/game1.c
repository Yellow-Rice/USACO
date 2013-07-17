/*
ID: philipy1
LANG: C
TASK: game1
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int sequence[100];
int max[100][100];
int min[100][100];
int N;

int main ()
{
    int i, j;
    int temp0, temp1;
    FILE *fin = fopen("game1.in", "r");
    fscanf(fin, "%d", &N);
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%d", &sequence[i]);
        max[i][i] = sequence[i];
        min[i][i] = 0;
    }
    fclose(fin);
    
    //i > j always holds.
    for (i = 1; i < N; ++i) {
        for (j = i - 1; j >= 0; --j) {
            temp0 = sequence[j] + min[i][j + 1];
            temp1 = sequence[i] + min[i - 1][j];
            max[i][j] = (temp0 > temp1) ? (temp0) : (temp1);
            min[i][j] = (temp0 > temp1) ? max[i][j + 1] : max[i - 1][j];
        }
    }
    
    FILE *fout = fopen("game1.out", "w");
    fprintf(fout, "%d %d\n", max[N - 1][0], min[N - 1][0]);
    fprintf(stderr, "%d %d\n", max[N - 1][0], min[N - 1][0]);
    fclose(fout);
    
    exit(0);
}
