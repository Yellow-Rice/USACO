/*
ID: philipy1
LANG: C
TASK: agrinet
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int N;
    int matrix[100][100];
    int distance[100];
    _Bool isInTree[100];
    //int parent[100];
    int treeSize, treeCost;
    int minLength, minIndex;
    int i, j;
    FILE *fin = fopen("agrinet.in", "r");
    fscanf(fin, "%d", &N);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            fscanf(fin, "%d", &matrix[i][j]);
        }
    }
    fclose(fin);
    
    printf("%d\n", N);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    //Minimum Spanning Tree, treat vertex 0 as the base.
    treeSize = 0;
    treeCost = 0;
    for (i = 1; i < N; ++i) {
        distance[i] = INT_MAX;
        isInTree[i] = 0;
        //parent[i] = -1;
    }
    distance[0] = 0;
    while (treeSize < N) {
        minLength = INT_MAX;
        for (i = 0; i < N; ++i) {
            if (!isInTree[i]) {
                if (minLength > distance[i]) {
                    minLength = distance[i];
                    minIndex = i;
                }
            }
        }
        
        if (minLength == INT_MAX) {
            fprintf(stderr, "Unconnected graph!\n");
            exit(1);
        }
        
        isInTree[minIndex] = 1;
        ++treeSize;
        treeCost += minLength;
        for (i = 0; i < N; ++i) {
            if (!isInTree[i] && distance[i] > matrix[i][minIndex] && i != minIndex) {
                distance[i] = matrix[i][minIndex];
                //parent[i] = minIndex;
            }
        }
    }
    
    FILE *fout = fopen("agrinet.out", "w");
    fprintf(fout, "%d\n", treeCost);
    fclose(fout);
    
    printf("%d\n", N);
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    for (i = 0; i < N; ++i) {
        printf("i = %d, distance = %d, isInTree = %d\n", i, distance[i], isInTree[i]);
    }
    
    exit(0);
}
