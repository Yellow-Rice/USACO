/*
ID: philipy1
LANG: C
TASK: zerosum
*/
#include <stdio.h>
#include <stdlib.h>

int N;
int powers3[10] = {1, 3, 9, 27, 81, 243, 729, 729 * 3, 729 * 9, 729 * 27};
int powers10[10] = {1E0, 1E1, 1E2, 1E3, 1E4, 1E5, 1E6, 1E7, 1E8, 1E9};
int answers[10][729 * 27];
char symbols[9];

int main()
{
    int i, j, temp, sum, count;
    FILE *fin = fopen("zerosum.in", "r");
    fscanf(fin, "%d", &N);
    fclose(fin);
    
    answers[1][0] = 1;
    answers[0][0] = 0;
    for (i = 2; i <= N; ++i) {
        for (j = 0; j < powers3[i - 1]; ++j) {
            if (j % 3 == 0) {
                count = 1;
                temp = j;
                sum = i;
                while (temp % 3 == 0 && count < i) {
                    sum += powers10[count] * (i - count);
                    ++count;
                    temp /= 3;
                }
                if (temp % 3 == 1) {
                    answers[i][j] = answers[i - count][temp / 3] + sum;
                }
                else if (temp % 3 == 2) {
                    answers[i][j] = answers[i - count][temp / 3] - sum;
                }
                else
                    answers[i][j] = sum;
                printf("i = %d, j = %d, sum = %d, answers[i][j] = %d\n", i, j, sum, answers[i][j]);
            }
            else if (j % 3 == 1) {
                answers[i][j] = answers[i - 1][j / 3] + i;
            }
            else {
                answers[i][j] = answers[i - 1][j / 3] - i;
            }
        }
    }
    
    FILE *fout = fopen("zerosum.out", "w");
    for (i = 0; i < powers3[N - 1]; ++i) {
        if (!answers[N][i]) {
            for (j = N - 1, temp = i; j > 0; --j, temp /= 3) {
                if (temp % 3 == 0) {
                    symbols[j] = ' ';
                }
                else if (temp % 3 == 1) {
                    symbols[j] = '+';
                }
                else {
                    symbols[j] = '-';
                }
            }
            printf("1");
            fprintf(fout, "1");
            for (j = 1; j < N; ++j) {
                printf("%c%d", symbols[j], j + 1);
                fprintf(fout, "%c%d", symbols[j], j + 1);
            }
            printf("\n");
            fprintf(fout, "\n");
        }
    }
    fclose(fout);
    
    exit(0);
}