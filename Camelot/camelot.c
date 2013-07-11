/*
ID: philipy1
LANG: C
TASK: camelot
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define Q_CAP   1000000
int q_col[Q_CAP];
int q_row[Q_CAP];
int q_first = 0;
int q_size = 0;

void clear()
{
    q_first = q_size = 0;
}

void push(int col, row)
{
    q_col[(q_first + q_szie) % Q_CAP] = col;
    q_row[(q_first + q_szie++) % Q_CAP] = row;
}

void pop(int *col, int *row)
{
    *col = q_col[(q_first + --q_szie) % Q_CAP];
    *row = q_row[(q_first + q_szie) % Q_CAP];
}

int R, C;
int king[2]; //{column, row}
int knights[26 * 30][2];
int count[27][31];
int steps[27][31];
int cost[27][31];
int prev[27][31];
int num = 0;

int dist_to_king(int col, int row)
{
    int d1 = col - king[0];
    int d2 = row - king[1];
    d1 = (d1 >= 0) ? d1 : -d1;
    d2 = (d2 >= 0) ? d2 : -d2;
    return (d1 > d2) ? d1 : d2;
}

int finish = INT_MAX;
int r, c;

void knight_move(int temp_c, int temp_r)
{
    if (temp_c > 0 && temp_r > 0 && temp_c <= C && temp_r <= R && count[temp_c][temp_r] > count[c][r]) {
        count[temp_c][temp_r] = count[c][r] + 1;
        if (count[temp_c][temp_r] > count[c][r] + 1 && steps[c][r] < dist_to_king(temp_c, temp_r)) {
            steps[temp_c][temp_r] = steps[c][r];
        }
        else if (count[temp_c][temp_r] > count[c][r] + 1 && steps[c][r] >= dist_to_king(temp_c, temp_r)) {
            steps[temp_c][temp_r] = dist_to_king(temp_c, temp_r);
        }
        else if (steps[c][r] < steps[temp_c][temp_r])){
            steps[temp_c][temp_r] = steps[c][r];
        }
        if (king[0] == temp_c && king[1] == temp_r) {
            finish = count[temp_c][temp_r];
        }
    }
}

int find_cost(int col, int row)
{
    int i, j, k;
    int min = INT_MAX;
    cost[col][row] = 0;
    finish = INT_MAX;
    for (k = 0; k < num; ++k) {
        for (i = 1; i <= C; ++i) {
            for (j = 1; j <= R; ++j) {
                steps[i][j] = dist_to_king(i, j);
                count[i][j] = INT_MAX;
            }
        }
        clear();
        push(knights[k][0], knights[k][1]);
        steps[knights[k][0], knights[k][1]] = 0;
        while (1) {
            pop(&c, &r);
            if (count[c][r] >= finish) {
                break;
            }
            knight_move(c - 2, r + 1);
            knight_move(c - 1, r + 2);
            knight_move(c + 1, r + 2);
            knight_move(c + 2, r + 1);
            knight_move(c + 2, r - 1);
            knight_move(c + 1, r - 2);
            knight_move(c - 1, r - 2);
            knight_move(c - 2, r - 1);
        }
        if (steps[king[0]][king[1]] < min) {
            min = steps[king[0]][king[1]];
        }
        cost[col][row] += count[king[0]][king[1]];
    }
    cost[col][row] += min;
    return cost[col][row];
}

// Calculate the minimum total steps cell by cell.
int init()
{
    int i, j;
    int min = INT_MAX;
    int ret;
    for (i = 1; i <= C; ++i) {
        for (j = 1; j <= R; ++j) {
            ret = find_cost(i, j);
            if (ret < min) {
                min = ret;
            }
        }
    }
    return ret;
}

int main()
{
    char col;
    int row;
    int ans;
    FILE *fin = fopen("camelot.in", "r");
    fscanf(fin, "%d %d\n", &R, &C);
    printf("%d %d\n", R, C);
    fscanf(fin, "%c %d\n", &col, &row);
    king[0] = col - 'A' + 1;
    king[1] = row;
    printf("%d %d\n", king[0], king[1]);
    while (2 == fscanf(fin, "%c %d\n", &col, &row)) {
        knights[num][0] = col - 'A' + 1;
        knights[num++][1] = row;
        printf("%d %d\n", knights[num - 1][0], knights[num - 1][1]);
    }
    fclose(fin);
    
    ans = init();
    
    FILE *fout = fopen("camelot.in", "w");
    fprintf(fout, "%d\n", ans);
    fprintf(stdout, "%d\n", ans);
    fclose(fout);
    
    exit(0);
}
