/*
ID: philipy1
LANG: C
TASK: money
*/
#include <stdio.h>
#include <stdlib.h>

long long V, N;
long long count[10001] = {1LL};
long long bases[25];

int main()
{
    int i, j, k;
    FILE *fin = fopen("money.in", "r");
    fscanf(fin, "%lld%lld", &V, &N);
    for (i = 0; i < V; ++i) {
        fscanf(fin, "%lld", bases + i);
    }
    fclose(fin);
    
    for (i = 1; i <= N; ++i) {
        count[i] = 0;
    }
    for (i = 0; i < V; ++i) {
        for (j = N - 1; j >= 0; --j) {
            if (count[j]) {
                for (k = j + bases[i]; k <= N; k += bases[i]) {
                    count[k] += count[j];
                }
            }
        }
    }
    
    /*for (i = 0; i < N; ++i)
        printf("%lld ", count[i]);
    printf("\n");*/
    
    FILE *fout = fopen("money.out", "w");
    fprintf(fout, "%lld\n", count[N]);
    fclose(fout);
    
    exit(0);
}
