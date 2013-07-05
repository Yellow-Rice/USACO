/*
ID: philipy1
LANG: C
TASK: nocows
*/
#include <stdio.h>
#include <stdlib.h>

int K, N;
int pedigrees[101][201];

int main()
{
    int i, j;
    int A, J, temp;
    FILE *fin = fopen("nocows.in", "r");
    fscanf(fin, "%d%d", &N, &K);
    fclose(fin);
    FILE *fout = fopen("nocows.out", "w");
    if (N % 2 == 0) {
        fprintf(fout, "%d\n", 0);
        fclose(fout);
        exit(0);
    }
    
    pedigrees[1][1] = 1;
    for (i = 3; i <= N; i += 2) {
        pedigrees[1][i] = 0;
    }
    for (i = 2; i <= K; ++i) {
        for (j = 1; j <= N; j += 2) {
            pedigrees[i][j] = 0;
            for (A = 1; A < j; A += 2) {
                if (pedigrees[i - 1][A]) {
                    temp = 0;
                    for (J = 1; J < i - 1; ++J) {
                        temp += pedigrees[J][j - A - 1];
                        temp %= 9901;
                    }
                    pedigrees[i][j] += (pedigrees[i - 1][A] * ((2 * temp + pedigrees[i - 1][j - A -  1]) % 9901)) % 9901;
                    pedigrees[i][j] %= 9901;
                }
            }
        }
    }
    
    for (i = 1; i <= K; ++i) {
        for (j = 1; j <= N; j += 2) {
            printf("%d %d ", pedigrees[i][j], 0);
        }
        printf("\n");
    }
    
    fprintf(fout, "%d\n", pedigrees[K][N]);
    printf("%d\n", pedigrees[K][N]);
    fclose(fout);
    
    exit(0);
}
