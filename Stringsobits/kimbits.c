/*
 ID: philipy1
 LANG: C
 TASK: kimbits
 */
 
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, L;
    long long I; //To store 1 x 32, the 2^32th number with N = L =32. From my test,long is not enough!
    int C[32][32];
    int ans[32];
    int length = 0;
    long long count;
    int i, j;
    FILE *fin = fopen("kimbits.in", "r");
    fscanf(fin, "%d %d %lld", &N, &L, &I); // Notice: use %lld for I!
    fclose(fin);
    
    //C[i + 1][j + 1] = C[i][j] + C[i + 1][j];
    for (j = 0; j < 32; ++j) { 
        C[0][j] = C[j][j] = 1;
        for (i = 1; i < j; ++i) {
            C[i][j] = C[i - 1][j - 1] + C[i][j - 1];
        }
    }
    
    for (i = 0; i < N; ++i) {
        count = 0;
        for (j = 0; j <= L && j <= N - i - 1; ++j) {
            count += C[j][N - i - 1];
        }
        if (count >= I) {
            ans[i] = 0;
        }
        else {
            ans[i] = 1;
            I -= count;
            --L;
        }
    }
    
    FILE *fout = fopen("kimbits.out", "w");
    for (i = 0; i < N; ++i) {
        fprintf(fout, "%d", ans[i]);
    }
    fprintf(fout, "\n");
    fclose(fout);
    
    exit(0);
}
