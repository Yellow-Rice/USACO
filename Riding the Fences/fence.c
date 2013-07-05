/*
 ID: philipy1
 LANG: C
 TASK: fence
 */
  
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int F;
    int degree[501];
    int matrix[501][501];
    int i, j, k;
    int a, b;
    int stack[1000000];
    int ans[100000];
    int last = 0;
    int size = 0;
    int odd[2], node = 0;
    for (i = 1; i <= 500; ++i) {
        for (j = 1; j <= 500; ++j) {
            matrix[i][j] = 0;
        }
        degree[i] = 0;
    }
    FILE *fin = fopen("fence.in", "r");
    fscanf(fin, "%d", &F);
    for (i = 0; i < F; ++i) {
        fscanf(fin, "%d %d", &a, &b);
        ++degree[a];
        ++degree[b];
        ++matrix[a][b];
        ++matrix[b][a];
    }
    fclose(fin);
    
    for (i = 1; node < 2 && i <= 500; ++i) {
        if (degree[i] % 2) {
            odd[node++] = i;
        }
    }
    if (node == 0) {
        stack[last++] = 1;
    }
    else {
        stack[last++] = odd[0] < odd[1] ? odd[0] : odd[1];
    }
    printf("stack[0] = %d\n", stack[0]);
    while(last) {
        node = stack[--last];
        if (!degree[node]) {
            ans[size++] = node;
        }
        else {
            for (i = 1; !matrix[i][node]; ++i) ;
            stack[last++] = node;
            stack[last++] = i;
            --degree[i];
            --degree[node];
            --matrix[i][node];
            --matrix[node][i];
        }
    }
    
    FILE *fout = fopen("fence.out", "w");
    for (i = size - 1; i >= 0; --i) {
        fprintf(fout, "%d\n", ans[i]);
    }
    fclose(fout);
    
    exit(0);
}
