/*
 ID: philipy1
 LANG: C
 TASK: shopping
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int s, b;
int min = INT_MAX;
int special[99][12];
int product[5][3];
int price[1000];
int quantity[1000];

void search(int sum, int start)
{
    int j;

    if (start < s) {
        for (j = 0; j < special[start][0]; ++j) {
            quantity[special[start][j * 2 + 1]] -= special[start][j * 2 + 2];
        }
        for (j = 0; quantity[special[start][j * 2 + 1]] >= 0 && j < special[start][0]; ++j) ;
        if (j == special[start][0] && min > sum + special[start][special[start][0] * 2 + 1]) {
            search(sum + special[start][special[start][0] * 2 + 1], start);
        }
        for (j = 0; j < special[start][0]; ++j) {
            quantity[special[start][j * 2 + 1]] += special[start][j * 2 + 2];
        }
    }

    if (start == s) {
        for (j = 0; j < b; ++j) {
            sum += quantity[product[j][0]] * product[j][2];
        }
        if (sum < min) {
            min = sum;
        }
    }
    else {
        search(sum, start + 1);
    }
}

int main()
{
    int n, k, c, p;
    int i, j;
    FILE *fin = fopen("shopping.in", "r");
    fscanf(fin, "%d", &s);
    for (i = 0; i < s; ++i) {
        fscanf(fin, "%d", &special[i][0]);
        for (j = 0; j < special[i][0]; ++j) {
            fscanf(fin, "%d %d", &special[i][j * 2 + 1], &special[i][j * 2 + 2]);
        }
        fscanf(fin, "%d", &special[i][j * 2 + 1]);
    }
    fscanf(fin, "%d", &b);
    for (i = 0; i < b; ++i) {
        fscanf(fin, "%d %d %d", &product[i][0], &product[i][1], &product[i][2]);
        quantity[product[i][0]] = product[i][1];
        price[product[i][0]] = product[i][2];
    }
    fclose(fin);
    
    search(0, 0);
    
    FILE *fout = fopen("shopping.out", "w");
    fprintf(fout, "%d\n", min);
    fclose(fout);
    
    exit(0);
}