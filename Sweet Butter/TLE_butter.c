/*
 ID: philipy1
 LANG: C
 TASK: butter
 */

/*Complexity: V^3*/
  
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int N, P, C;
    int dist[801][801];
    int pasture[801];
    int cow[1451];
    int i, j, k;
    int start, end, weight;
    int sum, min;
    FILE *fin = fopen("butter.in", "r");
    fscanf(fin, "%d %d %d", &N, &P, &C);
    for (i = 1; i <= P; ++i) {
        for (j = 1; j < i; ++j) {
            dist[i][j] = dist[j][i] = INT_MAX;
        }
        dist[i][i] = 0;
    }
    for (i = 1; i <= P; ++i) {
        pasture[i] = 0;
    }
    for (i = 1; i <= N; ++i) {
        fscanf(fin, "%d", &cow[i]);
        ++pasture[cow[i]];
    }
    for (i = 1; i <= C; ++i) {
        fscanf(fin, "%d %d %d", &start, &end, &weight);
        dist[start][end] = dist[end][start] = weight;
    }
    fclose(fin);
    
    //Floyd-Warshall Algorithm cost too much time
    for (k = 1; k <= P; ++k) {
        for (i = 1; i <= P; ++i) {
            for (j = 1; j <= P; ++j) { //use j < i will save half time, but still TLE T_T
                if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[j][i] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    min = INT_MAX;
    for (i = 1; i <= P; ++i) {
        sum = 0;
        for (j = 1; j <= P && (pasture[j] == 0 || dist[i][j] < INT_MAX); ++j) {
            sum += (pasture[j] * dist[i][j]);
        }
        if (sum < min && j > P) {
            min = sum;
        }
    }
    
    FILE *fout = fopen("butter.out", "w");
    fprintf(fout, "%d\n", min);
    fprintf(stdout, "%d\n", min);
    fclose(fout);
    
    exit(0);
}
