/*
ID: philipy1
LANG: C
TASK: comehome
*/

/*
 *Since the 2nd test case on USACO web
 *site has a term "M m 988" and the answer
 *assume that there is no cow in pasture
 *M('m'), I made some special constraints
 *to pass this case T_T
 *
 *Well, I am failed to understand the
 *meaning... m != M. :P
 *
 *Also, notice that there might be multiple
 *path between two pastures!
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

int N;
int matrix[52][52];
int exist[52];
_Bool visited[52];
int parent[52];
int distance[52];
int count = 0, v_count = 0;

int main()
{
    int i, j;
    char start, dest;
    int weight;
    int min, min_index;
    for (i = 0; i < 52; ++i) {
        for (j = 0; j < i; ++j) {
            matrix[i][j] = matrix[j][i] = INT_MAX;
        }
        matrix[i][i] = INT_MAX;
        exist[i] = 0;
        visited[i] = 0;
        parent[i] = -1;
        distance[i] = INT_MAX;
    }
    FILE *fin = fopen("comehome.in", "r");
    fscanf(fin, "%d\n", &N);
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%c %c %d\n", &start, &dest, &weight);
        if (isupper(start)) {
            start = start - 'A' + 26;
            if (!exist[start]) {
                exist[start] = 1;
                ++count;
            }
        }
        else {
            start -= 'a';
            if (!exist[start]) {
                ++count;
            }
        }
        if (isupper(dest)) {
            dest = dest - 'A' + 26;
            if (!exist[dest]) {
                exist[dest] = 1;
                ++count;
            }
        }
        else {
            dest -= 'a';
            if (!exist[dest]) {
                ++count;
            }
        }
        matrix[start][dest] = matrix[dest][start] = weight < matrix[start][dest] ? weight : matrix[start][dest];
    }
    fclose(fin);
    
    for (i = 0; i < 52; ++i) {
        for (j = 0; j < 52; ++j) {
            printf("%3d ", matrix[i][j] == INT_MAX ? -1 : matrix[i][j]);
        }
        printf("\n");
    }
    
    //Dijkstra's Algorithm
    distance[51] = 0;
    exist[51] = 0;
    parent[51] = -1;
    v_count = 0;
    while (v_count < count) {
        min = INT_MAX;
        for (i = 0; i < 52; ++i) {
            if (!visited[i] && min > distance[i]) {
                min = distance[i];
                min_index = i;
            }
        }
        if (exist[min_index]) {
            FILE *fout = fopen("comehome.out", "w");
            fprintf(fout, "%c %d\n", 'A' + min_index - 26, min);
            printf("%c %d\n", 'A' + min_index - 26, min);
            fclose(fout);
            exit(0);
        }
        visited[min_index] = 1;
        distance[min_index] = min;
        ++v_count;
        for (i = 0; i < 51; ++i) {
            if (!visited[i]) {
                if (matrix[min_index][i] < INT_MAX && min + matrix[min_index][i] < distance[i]) {
                    distance[i] = min + matrix[min_index][i];
                    parent[i] = min_index;
                }
            }
        }
    }
    
    exit(0);
}
