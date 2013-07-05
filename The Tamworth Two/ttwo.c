/*
ID: philipy1
LANG: C
TASK: ttwo
*/
#include <stdio.h>
#include <stdlib.h>

char map[10][10];
int x_C, y_C, x_F, y_F;
int d_C = 0, d_F = 0; //0, 1, 2, 3 represent N, E, S, W respectively

int main()
{
    int i, j;
    FILE *fin = fopen("ttwo.in", "r");
    for (i = 0; i < 10; ++i) {
        for (j = 0; j < 10; ++j) {
            fscanf(fin, "%c", &map[i][j]);
            printf("%c", map[i][j]);
            if (map[i][j] == 'C') {
                x_C = j;
                y_C = i;
            }
            else if (map[i][j] == 'F') {
                x_F = j;
                y_F = i;
            }
        }
        fscanf(fin, "\n");
        printf("\n");
    }
    fclose(fin);
    
    for (i = 1; i <10000; ++i) {
        printf("d_C = %d, x_C = %d, y_C = %d\nd_F = %d, x_F = %d, y_F = %d\n", d_C, x_C, y_C, d_F, x_F, y_F);
        switch (d_C) {
            case 0:
                if (y_C == 0 || map[y_C - 1][x_C] == '*') {
                    d_C = 1;
                }
                else {
                    --y_C;
                }
                break;
            case 1:
                if (x_C == 9 || map[y_C][x_C + 1] == '*') {
                    d_C = 2;
                }
                else {
                    ++x_C;
                }
                break;
            case 2:
                if (y_C == 9 || map[y_C + 1][x_C] == '*') {
                    d_C = 3;
                }
                else {
                    ++y_C;
                }
                break;
            case 3:
                if (x_C == 0 || map[y_C][x_C - 1] == '*') {
                    d_C = 0;
                }
                else {
                    --x_C;
                }
                break;
        }
        switch (d_F) {
            case 0:
                if (y_F == 0 || map[y_F - 1][x_F] == '*') {
                    d_F = 1;
                }
                else {
                    --y_F;
                }
                break;
            case 1:
                if (x_F == 9 || map[y_F][x_F + 1] == '*') {
                    d_F = 2;
                }
                else {
                    ++x_F;
                }
                break;
            case 2:
                if (y_F == 9 || map[y_F + 1][x_F] == '*') {
                    d_F = 3;
                }
                else {
                    ++y_F;
                }
                break;
            case 3:
                if (x_F == 0 || map[y_F][x_F - 1] == '*') {
                    d_F = 0;
                }
                else {
                    --x_F;
                }
                break;
        }
        if (x_C == x_F && y_C == y_F) {
            break;
        }
    }
    
    FILE *fout = fopen("ttwo.out", "w");
    if (i == 10000) {
        fprintf(fout, "0\n");
    }
    else {
        fprintf(fout, "%d\n", i);
    }
    fclose(fout);
    
    exit(0);
}
