/*
 ID: philipy1
 LANG: C
 TASK: rect1
 */
 
#include <stdio.h>
#include <stdlib.h>

int llx[10000], lly[10000], urx[10000], ury[10000], colors[10000];

int main()
{
    int A, B, N;
    int results[2501];
    int i, j, k;
    FILE *fin = fopen("rect1.in", "r");
    fscanf(fin, "%d %d %d", &A, &B, &N);
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%d %d %d %d %d", &llx[i], &lly[i], &urx[i], &ury[i], &colors[i]);
    }
    fclose(fin);
    
    for (i = 0; i < 2501; ++i) {
        results[i] = 0;
    }
    
    for (i = 0; i < B; ++i) {
        for (j = 0; j < A; ++j) {
            for (k = N - 1; k >= 0; --k) {
                if (j >= llx[k] && i >= lly[k] && j < urx[k] && i < ury[k]) {
                    ++results[colors[k]];
                    break;
                }
            }
            if (k < 0) {
                ++results[1];
            }
        }
    }
    
    FILE *fout = fopen("rect1.out", "w");
    for (i = 1; i < 2501; ++i) {
        if (results[i]) {
            fprintf(fout, "%d %d\n", i, results[i]);
        }
    }
    fclose(fout);
    
    exit(0);
}
