/*
ID: philipy1
LANG: C
TASK: fracdec
*/
#include <stdio.h>
#include <stdlib.h>

int N, D;
int digits[1000000], count = 0;
_Bool flags[100000];
int position[100000];

int main()
{
    FILE *fin = fopen("fracdec.in", "r");
    fscanf(fin, "%d%d", &N, &D);
    fclose(fin);
    
    int left = N / D;
    N = N % D;
    int i, j, n = 1, temp = left;
    for (i = 0; i < D; ++i) {
        flags[i] = 0;
    }
    while (temp) {
        temp /= 10;
        ++n;
    }
    if (left == 0) {
        n = 2;
    }
    
    while (N && !flags[N]) {
        printf("N = %d,\tcount = %d\n", N, count);
        flags[N] = 1;
        position[N] = count;
        N = N * 10;
        digits[count++] = N / D;
        N = N % D;
    }
    printf("N = %d,\tcount = %d\n", N, count);
    
    FILE *fout = fopen("fracdec.out", "w");
    if (N) {
        fprintf(fout, "%d.", left);
        printf("%d.", left);
        for (i = 0; i < position[N]; ++i) {
            fprintf(fout, "%d", digits[i]);
            printf("%d", digits[i]);
            ++n;
            if (n % 76 == 0) {
                fprintf(fout, "\n");
                printf("\n");
            }
        }
        fprintf(fout, "(");
        printf("(");
        ++n;
        for (i = position[N]; i < count; ++i) {
            if (n % 76 == 0) {
                fprintf(fout, "\n");
                printf("\n");
            }
            fprintf(fout, "%d", digits[i]);
            printf("%d", digits[i]);
            ++n;
        }
        if (n % 76 == 0) {
            fprintf(fout, "\n");
            printf("\n");
        }
        fprintf(fout, ")\n");
        printf(")\n");
    }
    else {
        if (count == 0) {
            fprintf(fout, "%d.0\n", left);
            printf("%d.0\n", left);
        }
        else {
            fprintf(fout, "%d.", left);
            printf("%d.", left);
            for (i = 0; i < count; ++i) {
                if (n % 76 == 0) {
                    fprintf(fout, "\n");
                    printf("\n");
                }
                fprintf(fout, "%d", digits[i]);
                printf("%d", digits[i]);
                ++n;
            }
            fprintf(fout, "\n");
            printf("\n");
        }
    }
    fclose(fin);
    
    exit(0);
}
