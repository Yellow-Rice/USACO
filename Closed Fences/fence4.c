/*
ID: philipy1
LANG: C
TASK: fence4
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int N;
int x[201];
int y[201];

int cross_product2(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - x2 * y1;
}

_Bool intersect(int i, int j)
{
    if (cross_product2(x[i + 1] - x[i], y[i + 1] - y[i], x[j] - x[i], y[j] - y[i]) * cross_product2(x[i + 1] - x[i], y[i + 1] - y[i], x[j + 1] - x[i], y[j + 1] - y[i]) > 0) {
        return 0;
    }
    if (cross_product2(x[j + 1] - x[j], y[j + 1] - y[j], x[i] - x[j], y[i] - y[j]) * cross_product2(x[j + 1] - x[j], y[j + 1] - y[j], x[i + 1] - x[j], y[i + 1] - y[j]) > 0) {
        return 0;
    }
    return 1;
}

_Bool check()
{
    int i, j;
    for (i = 0; i < N; ++i) {
        //check overlaping
        if (i + 1 < N && cross_product2(x[i + 1] - x[i], y[i + 1] - y[i], x[i + 2] - x[i], y[i + 2] - y[i]) && (x[i + 2] - x[i]) * (x[i + 2] -x[i + 1]) <= 0) {
            return 0;
        }
        //check intersection
        for (j = i + 2; j < N; ++j) {
            if (intersect(i, j)) {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    int i;
    FILE *fin = fopen("fence4.in", "r");
    fscanf(fin, "%d", &N);
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%d %d", &x[i], &y[i]);
    }
    fclose(fin);
    x[N] = x[0];
    y[N] = y[0];
    
    FILE *fout = fopen("fence4.out", "w");
    if (check()) {
        
    }
    else {
        fprintf(fout, "NOFENCE\n");
        fprintf(stderr, "NOFENCE\n");
    }
    
    exit(0);
}
