/*
 ID: philipy1
 LANG: C
 TASK: inflate
 */

/*
 *See the description of knapsack problem on wikipedia.org
 *http://en.wikipedia.org/wiki/Knapsack_problem
 *inflate is a UKP TAT...
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int M, N;
    int points[10001];
    int minutes[10001];
    int maxScores[10001];
    int max;
    int i, j;
    FILE *fin = fopen("inflate.in", "r");
    fscanf(fin, "%d %d", &M, &N);
    for (i = 1; i <= N; ++i) {
        fscanf(fin, "%d %d", &points[i], &minutes[i]);
    }
    fclose(fin);
	
    maxScores[0] = 0;
    for (i = 1; i <= M; ++i) {
        max = 0;
        for (j = 1; j <= N; ++j) {
            if (minutes[j] <= i && points[j] + maxScores[i - minutes[j]] > max) {
                max = points[j] + maxScores[i - minutes[j]];
            }
        }
        maxScores[i] = max;
    }
    
    FILE *fout = fopen("inflate.out", "w");
    fprintf(fout, "%d\n", max);
    fclose(fout);
    
    exit(0);
}
