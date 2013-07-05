/*
ID: philipy1
LANG: C++
TASK: maze1
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bfs(int x, int y, int map[][100]);

int W, H;
char maze[300][100];
int map1[300][100];
int map2[300][100];
int d1_x = 0, d1_y = 0, d2_x = 0, d2_y = 0;
int max = 0;
int x_q[100000], y_q[100000], first, length;
int width, height;

int main()
{
    FILE *fin = fopen("maze1.in", "r");
    fscanf(fin, "%d %d\n", &W, &H);
    printf("%d %d\n", W, H);
    int i, j, temp = 0;
    int *p;
    width = 2 * W + 1;
    height = 2 * H + 1;
    for (i = 0; i < height; ++i) {
        fgets(maze[i], 100, fin);
        printf("%s", maze[i]);
    }
    fclose(fin);
    
    for (i = 1; i < height; i += 2) {
        if (' ' == maze[i][0]) {
            if (temp) {
                d2_x = 1;
                d2_y = i;
            }
            else {
                d1_x = 1;
                d1_y = i;
                temp = 1;
            }
        }
        if (' ' == maze[i][width - 1]) {
            if (temp) {
                d2_x = width - 2;
                d2_y = i;
            }
            else {
                d1_x = width - 2;
                d1_y = i;
                temp = 1;
            }
        }
    }
    for (j = 1; j < width; j += 2) {
        if (' ' == maze[0][j]) {
            if (temp) {
                d2_x = j;
                d2_y = 1;
            }
            else {
                d1_x = j;
                d1_y = 1;
                temp = 1;
            }
        }
        if (' ' == maze[height - 1][j]) {
            if (temp) {
                d2_x = j;
                d2_y = height - 2;
            }
            else {
                d1_x = j;
                d1_y = height - 2;
                temp = 1;
            }
        }
    }
    printf("%d %d\n%d %d\n", d1_x, d1_y, d2_x, d2_y);
    
    bfs(d1_x, d1_y, map1);
    bfs(d2_x, d2_y, map2);
    for (i = 1; i < height; i += 2) {
        for (j = 1; j < width; j += 2) {
            if (map1[i][j] > max && map2[i][j] > max) {
                max = map1[i][j] < map2[i][j] ? map1[i][j] : map2[i][j];
            }
        }
    }
    
    FILE *fout = fopen("maze1.out", "w");
    fprintf(fout, "%d\n", max);
    fclose(fout);
    
    exit(0);
}

void bfs(int x, int y, int map[][100])
{
    int i, j;
    first = length = 0;
    x_q[first + length] = x;
    y_q[first + length++] = y;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            map[i][j] = 0;
        }
    }
    map[y][x] = 1;
    
    while (length) {
        x = x_q[first];
        y = y_q[first++];
        first = first % 100000;
        --length;
        if (maze[y][x - 1] == ' ' && x > 1 && map[y][x - 2] == 0) {
            map[y][x - 2] = map[y][x] + 1;
            x_q[first + length] = x - 2;
            y_q[first + length++] = y;
        }
        if (maze[y - 1][x] == ' ' && y > 1 && map[y - 2][x] == 0) {
            map[y - 2][x] = map[y][x] + 1;
            x_q[first + length] = x;
            y_q[first + length++] = y - 2;
        }
        if (maze[y][x + 1] == ' ' && x < width - 2 && map[y][x + 2] == 0) {
            map[y][x + 2] = map[y][x] + 1;
            x_q[first + length] = x + 2;
            y_q[first + length++] = y;
        }
        if (maze[y + 1][x] == ' ' && y < height - 2 && map[y + 2][x] == 0) {
            map[y + 2][x] = map[y][x] + 1;
            x_q[first + length] = x;
            y_q[first + length++] = y + 2;
        }
    }
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
}
