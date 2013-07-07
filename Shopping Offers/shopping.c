/*
 ID: philipy1
 LANG: C
 TASK: shopping
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cost[6][6][6][6][6];
int index[5] = {0, 0, 0, 0, 0};

int s, b;
int special[99][12];
int product[5][3]; //{code, quantity, price}
int number[1000];
int price[1000];
int quantity[1000];

void calc()
{
    if(!index[0] && !index[1] && !index[2] && !index[3] && !index[4]) {
        return ;
    }

    int i, j;
    int min = INT_MAX;
    int remaining[5];
    //add single item
    if (0 < b && index[0] && min > (product[0][2] + cost[index[0] - 1][index[1]][index[2]][index[3]][index[4]])) min = product[0][2] + cost[index[0] - 1][index[1]][index[2]][index[3]][index[4]];
    if (1 < b && index[1] && min > (product[1][2] + cost[index[0]][index[1] - 1][index[2]][index[3]][index[4]])) min = product[1][2] + cost[index[0]][index[1] - 1][index[2]][index[3]][index[4]];
    if (2 < b && index[2] && min > (product[2][2] + cost[index[0]][index[1]][index[2] - 1][index[3]][index[4]])) min = product[2][2] + cost[index[0]][index[1]][index[2] - 1][index[3]][index[4]];
    if (3 < b && index[3] && min > (product[3][2] + cost[index[0]][index[1]][index[2]][index[3] - 1][index[4]])) min = product[3][2] + cost[index[0]][index[1]][index[2]][index[3] - 1][index[4]];
    if (4 < b && index[4] && min > (product[4][2] + cost[index[0]][index[1]][index[2]][index[3]][index[4] - 1])) min = product[4][2] + cost[index[0]][index[1]][index[2]][index[3]][index[4] - 1];
    //use special offer
    for (i = 0; i < s; ++i) {
        for (j = 0; j < 5; ++j) {
            remaining[j] = index[j];
        }
        for (j = 0; j < special[i][0]; ++j) {
            if (index[number[special[i][2 * j + 1]]] < special[i][2 * j + 2])    break;
            remaining[number[special[i][2 * j + 1]]] -= special[i][2 * j + 2];
        }
        if (j == special[i][0]) {
            if (min > special[i][j * 2 + 1] + cost[remaining[0]][remaining[1]][remaining[2]][remaining[3]][remaining[4]]) {
                min = special[i][j * 2 + 1] + cost[remaining[0]][remaining[1]][remaining[2]][remaining[3]][remaining[4]];
            }
        }
    }
    cost[index[0]][index[1]][index[2]][index[3]][index[4]] = min;
}

void init()
{
    cost[0][0][0][0][0] = 0;
    for (index[0] = 0; index[0] < 6; ++index[0]) {
        for (index[1] = 0; index[1] < 6; ++index[1]) {
            for (index[2] = 0; index[2] < 6; ++index[2]) {
                for (index[3] = 0; index[3] < 6; ++index[3]) {
                    for (index[4] = 0; index[4] < 6; ++index[4]) {
                        calc();
                    }
                }
            }
        }
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
        number[product[i][0]] = i;
        quantity[product[i][0]] = product[i][1];
        price[product[i][0]] = product[i][2];
    }
    fclose(fin);

    init();
    index[0] = (0 < b) ? product[0][1] : 0;
    index[1] = (1 < b) ? product[1][1] : 0;
    index[2] = (2 < b) ? product[2][1] : 0;
    index[3] = (3 < b) ? product[3][1] : 0;
    index[4] = (4 < b) ? product[4][1] : 0;

    FILE *fout = fopen("shopping.out", "w");
    fprintf(fout, "%d\n", cost[index[0]][index[1]][index[2]][index[3]][index[4]]);
    fclose(fout);

    exit(0);
}
