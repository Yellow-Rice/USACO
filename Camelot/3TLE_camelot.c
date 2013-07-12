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
int num = 0;

int kdist[27][31];
int dist_to_king(int col, int row)
{
    int d1 = col - king[0];
    int d2 = row - king[1];
    d1 = (d1 >= 0) ? d1 : -d1;
    d2 = (d2 >= 0) ? d2 : -d2;
    return (d1 > d2) ? d1 : d2;
}
int matrix[27][31][27][31]; //start_col, start_row, dest_col, dest_row
int total[27][31]; //steps of every knight move to the cell

void init_matrix(int col, int row)
{
    int i, j;
    int count;
    int c, r;
    for (i = 1; i <= C; ++i) {
        for (j = 1; j <= R; ++j) {
            matrix[col][row][i][j] = INT_MAX;
        }
    }
    matrix[col][row][col][row] = 0;
    clear();
    push(col, row);
    while(q_size) {
        pop(&c, &r);
        count = matrix[col][row][c][r] + 1;
        if (c - 2 > 0   && r - 1 > 0    && count < matrix[col][row][c - 2][r - 1]) {matrix[col][row][c - 2][r - 1] = count; push(c - 2, r - 1);}
        if (c - 2 > 0   && r + 1 <= R   && count < matrix[col][row][c - 2][r + 1]) {matrix[col][row][c - 2][r + 1] = count; push(c - 2, r + 1);}
        if (c - 1 > 0   && r - 2 > 0    && count < matrix[col][row][c - 1][r - 2]) {matrix[col][row][c - 1][r - 2] = count; push(c - 1, r - 2);}
        if (c - 1 > 0   && r + 2 <= R   && count < matrix[col][row][c - 1][r + 2]) {matrix[col][row][c - 1][r + 2] = count; push(c - 1, r + 2);}
        if (c + 1 <= C  && r - 2 > 0    && count < matrix[col][row][c + 1][r - 2]) {matrix[col][row][c + 1][r - 2] = count; push(c + 1, r - 2);}
        if (c + 1 <= C  && r + 2 <= R   && count < matrix[col][row][c + 1][r + 2]) {matrix[col][row][c + 1][r + 2] = count; push(c + 1, r + 2);}
        if (c + 2 <= C  && r - 1 > 0    && count < matrix[col][row][c + 2][r - 1]) {matrix[col][row][c + 2][r - 1] = count; push(c + 2, r - 1);}
        if (c + 2 <= C  && r + 1 <= R   && count < matrix[col][row][c + 2][r + 1]) {matrix[col][row][c + 2][r + 1] = count; push(c + 2, r + 1);}
    }
}

// Initilize kdist[][], matrix[][][][] for further use
void init()
{
    int i, j, k, l;
    for (i = 1; i <= C; ++i) {
        for (j = 1; j <= R; ++j) {
            // find the min dist between king with every cell
            kdist[i][j] = dist_to_king(i, j);
            // find the min dist between every 2 cells
            init_matrix(i, j);
            // find the total steps for all knights moving to every cell
            total[i][j] = 0;
            for (k = 0; k < num; ++k) {
                total[i][j] += matrix[i][j][knights[k][0]][knights[k][1]];
            }
        }
    }
}

int calc(int col, int row)
{
    int min = INT_MAX;
    int cost, temp;
    int i, j, k;
    //enumerate knight who pick up the king
    for (k = 0; k < num; ++k) {
        temp = total[col][row] - matrix[col][row][knights[k][0]][knights[k][1]];
        //enumerate meeting place of the king and the knight
        for (i = 1; i <= C; ++i) {
            for (j = 1; j <= R; ++j) {
                cost = temp;
                cost += kdist[i][j];
                cost += matrix[i][j][knights[k][0]][knights[k][1]];
                cost += matrix[col][row][i][j];
                if (cost < min) {
                    min = cost;
                }
            }
        }
    }
    return min;
}

int find_ans()
{
    if (num == 0) {
        return 0;
    }
    
    init();
    
    int i, j;
    int min = INT_MAX;
    int temp;
    for (i = 1; i < C; ++i) {
        for (j = 1; j < R; ++j) {
            temp = calc(i, j);
            if (min > temp) {
                min = temp;
            }
        }
    }
    
    return min;
}

int main()
{
    char col;
    int row;
    FILE *fin = fopen("camelot.in", "r");
    fscanf(fin, "%d %d\n", &R, &C);
    fscanf(fin, "%c %d\n", &col, &row);
    king[0] = col - 'A' + 1;
    king[1] = row;
    while (2 == fscanf(fin, "%c %d\n", &col, &row)) {
        knights[num][0] = col - 'A' + 1;
        knights[num++][1] = row;
    }
    fclose(fin);
    
    int ans;
    ans = find_ans();
    
    FILE *fout = fopen("camelot.out", "w");
    fprintf(fout, "%d\n", ans);
    fprintf(stderr, "%d\n", ans);
    fclose(fout);
    
    exit(0);
}
