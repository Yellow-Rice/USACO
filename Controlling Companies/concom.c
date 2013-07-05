/*
ID: philipy1
LANG: C
TASK: concom
*/
#include <stdio.h>
#include <stdlib.h>

int N;
_Bool controls[101][101];
int ownerships[101][101];
int ownerships2[101][101];

void flush1(int a, int b)
{
    int j;
    for (j = 1; j <= 100; ++j) {
        if (!controls[a][j] && ownerships[b][j]) {
            ownerships2[a][j] += ownerships[b][j];
            if (ownerships2[a][j] > 50) {
                controls[a][j] = 1;
                flush1(a, j);
            }
        }
    }
}

void flush2(int a, int b)
{
    int j, p = ownerships[a][b];
    for (j = 1; j <= 100; ++j) {
        if (controls[j][a] && !controls[j][b]) {
            ownerships2[j][b] += p;
            if (ownerships2[j][b] > 50) {
                controls[j][b] = 1;
                flush1(j, b);
            }
        }
    }
}

int main()
{
    int i, j, a, b, p;
    FILE *fin = fopen("concom.in", "r");
    fscanf(fin, "%d", &N);
    for (i = 1; i <= 100; ++i) {
        for (j = 1; j <= 100; ++j) {
            ownerships2[i][j] = ownerships[i][j] = controls[i][j] = 0;
        }
        controls[i][i] = 1;
        ownerships2[i][i] = ownerships[i][i] = 100;
    }
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%d%d%d", &a, &b, &p);
        ownerships[a][b] = p;
        flush2(a, b);
    }
    fclose(fin);
    
    FILE *fout = fopen("concom.out", "w");
    for (i = 1; i <= 100; ++i) {
        for (j = 0; j <= 100; ++j) {
            if (controls[i][j] && i != j) {
                fprintf(fout, "%d %d\n", i, j);
            }
        }
    }
    fclose(fout);
    
    exit(0);
}
