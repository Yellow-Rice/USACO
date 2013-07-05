/*
 ID: philipy1
 LANG: C
 TASK: stamps
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count[2000001];

int main()
{
    int K, N;
    int stamps[50];
    int i, j;
    FILE *fin = fopen("stamps.in", "r");
    fscanf(fin, "%d %d", &K, &N);
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%d", &stamps[i]);
    }
    fclose(fin);
    
    for (i = 1; i < 2000001; ++i) {
        count[i] = INT_MAX;
    }
    for (i = 0; count[i] <= K; ++i) {
        for (j = 0; j < N; ++j) {
            if (count[i] + 1 <= K && count[i] + 1 < count[i + stamps[j]]) {
                count[i + stamps[j]] = count[i] + 1;
            }
        }
    }
    
    FILE *fout = fopen("stamps.out", "w");
    fprintf(fout, "%d\n", i - 1);
    fclose(fout);
    
    exit(0);
}
