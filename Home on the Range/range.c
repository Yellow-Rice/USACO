/*
ID: philipy1
LANG: C
TASK: range
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int N;
int pasture[260][260];
int count[260][260];
int ans[261];

int main ()
{
    char row[261];
    int i, j, k;
    int temp;
    FILE *fin = fopen("range.in", "r");
    fscanf(fin, "%d\n", &N);
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%s", row);
        for (j = 0; j < N; ++j) {
            pasture[i][j] = row[j] - '0';
            count[i][j] = 0;
        }
        ans[i + 1] = 0;
    }
    fclose(fin);
    
    for (i = 0; i < N; ++i) {
        count[N - 1][i] = pasture[N - 1][i];
        count[i][N - 1] = pasture[i][N - 1];
        ans[1] += pasture[i][N - 1] + pasture[N - 1][i];
    }
    ans[1] -= pasture[N - 1][N - 1];
    
    for (i = N - 2; i >= 0; --i) {
        for (j = N - 2; j >= 0; --j) {
            if (pasture[i][j]) {
                temp = (count[i + 1][j] < count[i][j + 1]) ? count[i + 1][j] : count[i][j + 1];
                count[i][j] = 1 + ((temp < count[i + 1][j + 1]) ? temp : count[i + 1][j + 1]);
                for (k = 1; k <= count[i][j]; ++k) {
                    ++ans[k];
                }
            }
        }
    }
    
    FILE *fout = fopen("range.out", "w");
    for (k = 2; k <= N && ans[k]; ++k) {
        fprintf(fout, "%d %d\n", k, ans[k]);
        fprintf(stderr, "%d %d\n", k, ans[k]);
    }
    fclose(fout);
    
    exit(0);
}
