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

void push(int col, int row)
{
    if (q_size == Q_CAP) {
        fprintf(stderr, "push to FULL queue!\n");
        exit(-2);
    }
    q_col[(q_first + q_size) % Q_CAP] = col;
    q_row[(q_first + q_size) % Q_CAP] = row;
    q_size = (q_size + 1) % Q_CAP;
}

void pop(int *col, int *row)
{
    if (q_size == 0) {
        fprintf(stderr, "pop from EMPTY queue!\n");
        exit(-1);
    }
    *col = q_col[q_first % Q_CAP];
    *row = q_row[q_first % Q_CAP];
    q_first = (q_first + 1) % Q_CAP;
    --q_size;
}

int R, C;
int king[2]; //{column, row}
int knights[26 * 30][2];
int count[27][31];
int steps[27][31];
int cost[27][31];
//int prev[27][31];
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

void knight_move(const int c2, const int r2, const int d_col, const int d_row, const int s_col, const int s_row)
{
    if (c2 > 0 && r2 > 0 && c2 <= C && r2 <= R && count[c2][r2] > count[s_col][s_row]) {
        if (count[c2][r2] == count[s_col][s_row] + 1 && steps[s_col][s_row] < steps[c2][r2]) {
            steps[c2][r2] = steps[s_col][s_row];
            return ;
        }
        if (steps[s_col][s_row] <= dist_to_king(c2, r2)) {
            steps[c2][r2] = steps[s_col][s_row];
        }
        else {
            steps[c2][r2] = dist_to_king(c2, r2);
        }
        count[c2][r2] = count[s_col][s_row] + 1;
        if (d_col == c2 && d_row == r2) {
            finish = count[c2][r2];
            //printf("count = %d, steps = %d\n", count[c2][r2], steps[c2][r2]);
        }
        else {
            push(c2, r2);
            //printf("push(%d, %d)\n", c2, r2);
        }
    }
}

int find_cost(int col, int row)
{
    int i, j, k;
    int min = INT_MAX;
    int r, c;
    cost[col][row] = 0;
    for (k = 0; k < num; ++k) {
        //printf("knight %d %d: ", knights[k][0], knights[k][1]);
        if (knights[k][0] == col && knights[k][1] == row) {
            //printf("count[col][row] = %d\n", 0);
            if (min < dist_to_king(col, row)) {
                min = dist_to_king(col, row);
            }
            continue;
        }
        for (i = 1; i <= C; ++i) {
            for (j = 1; j <= R; ++j) {
                steps[i][j] = dist_to_king(i, j);
                count[i][j] = INT_MAX - 1;
            }
        }
        clear();
        finish = INT_MAX;
        push(knights[k][0], knights[k][1]);
        count[knights[k][0]][knights[k][1]] = 0;
        while (q_size) {
            pop(&c, &r);
            if (count[c][r] >= finish) {
                break;
            }
            knight_move(c - 2, r + 1, col, row, c, r);
            knight_move(c - 1, r + 2, col, row, c, r);
            knight_move(c + 1, r + 2, col, row, c, r);
            knight_move(c + 2, r + 1, col, row, c, r);
            knight_move(c + 2, r - 1, col, row, c, r);
            knight_move(c + 1, r - 2, col, row, c, r);
            knight_move(c - 1, r - 2, col, row, c, r);
            knight_move(c - 2, r - 1, col, row, c, r);
        }
        if (steps[col][row] < min) {
            min = steps[col][row];
        }
        cost[col][row] += count[col][row];
        //printf("count[col][row] = %d\n", count[col][row]);
    }
    cost[col][row] += min;
    return cost[col][row];
}

// Calculate the minimum total steps cell by cell.
int init()
{
    if (0 == num) {
        return 0;
    }
    int i, j;
    int min = INT_MAX;
    int ret;
    for (i = 1; i <= C; ++i) {
        for (j = 1; j <= R; ++j) {
            //printf("round %d %d\n", i, j);
            ret = find_cost(i, j);
            //printf("cost: %d\n\n", ret);
            if (ret < min) {
                min = ret;
            }
        }
    }
    return min;
}

int main()
{
    char col;
    int row;
    int ans;
    FILE *fin = fopen("camelot.in", "r");
    fscanf(fin, "%d %d\n", &R, &C);
    //printf("%d %d\n", R, C);
    fscanf(fin, "%c %d\n", &col, &row);
    king[0] = col - 'A' + 1;
    king[1] = row;
    //printf("%d %d\n", king[0], king[1]);
    while (2 == fscanf(fin, "%c %d\n", &col, &row)) {
        knights[num][0] = col - 'A' + 1;
        knights[num++][1] = row;
        //printf("%d %d\n", knights[num - 1][0], knights[num - 1][1]);
    }
    fclose(fin);
    
    ans = init();
    
    FILE *fout = fopen("camelot.out", "w");
    fprintf(fout, "%d\n", ans);
    fprintf(stdout, "%d\n", ans);
    fclose(fout);
    
    exit(0);
}
