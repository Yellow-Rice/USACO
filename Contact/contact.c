/*
 ID: philipy1
 LANG: C
 TASK: contact
 */
 
#include <stdio.h>
#include <stdlib.h>

const int POWER2[13] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
char ans[13];

char *toBinary(int size, int n)
{
    ans[size] = '\0';
    while(size) {
        ans[--size] = n % 2 + '0';
        n >>= 1;
    }
    return ans;
}

int main()
{
    int A, B, N;
    int count[13][4096];
    int previous[12] = {0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    char ch;
    int max_size, max_index, max, prev_max;
    int out_count;
    int i, j, k;
    for (i = 1; i <= 12; ++i) {
        for (j = 0; j < POWER2[i]; ++j) {
            count[i][j] = 0;
        }
    }
    FILE *fin = fopen("contact.in", "r");
    fscanf(fin, "%d %d %d", &A, &B, &N);
    ch = fgetc(fin);
    while(ch != EOF) {
        if (ch == '\n') {
            ch = fgetc(fin);
            continue;
        }
        ch -= '0';
        for (i = 12; i >= 1; --i) {
            if (previous[i - 1] >= 0) {
                ++count[i][previous[i] = previous[i - 1] * 2 + ch];
            }
        }
        ch = fgetc(fin);
    }
    fclose(fin);

    FILE *fout = fopen("contact.out", "w");
    prev_max = -1;
    out_count = 0;
    for (i = 0; i <= N;) {
        max = -1;
        for (j = A; j <= B; ++j) {
            for (k = 0; k < POWER2[j]; ++k) {
                if (count[j][k] > max) {
                    max = count[j][k];
                    max_size = j;
                    max_index = k;
                }
            }
        }
        if (!max) {
            break;
        }
        if (prev_max == -1) {
            fprintf(fout, "%d\n", max);
            i = 1;
            out_count = 1;
        }
        else if (prev_max != max) {
            if (++i > N) {
                break;
            }
            fprintf(fout, "\n%d\n", max);
            out_count = 1;
        }
        else {
            if (out_count == 6) {
                fprintf(fout, "\n");
                out_count = 1;
            }
            else {
                fprintf(fout, " ");
                ++out_count;
            }
        }
        fprintf(fout, "%s", toBinary(max_size, max_index));
        count[max_size][max_index] = 0;
        prev_max = max;
    }
    fprintf(fout, "\n");
    fclose(fout);
    
    exit(0);
}
