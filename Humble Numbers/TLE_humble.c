/*
 ID: philipy1
 LANG: C
 TASK: humble
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 999983 //A prime number
int table[TABLE_SIZE];

_Bool exist(const int i)
{
    int index;
    for (index = i % TABLE_SIZE; table[index] != -1 && table[index] != i; index = (index + 1) % TABLE_SIZE) ;
    return table[index] == i;
}

void set(int i)
{
    int index;
    for (index = i % TABLE_SIZE; table[index] != -1 && table[index] != i; index = (index + 1) % TABLE_SIZE) ;
    table[index] = i;
}

int main()
{
    int K, N;
    int primes[100];
    int count = 0;
    int nth = 2;
    int i, j;
    FILE *fin = fopen("humble.in", "r");
    fscanf(fin, "%d %d", &K, &N);
    for (i = 0; i < K; ++i) {
        fscanf(fin, "%d", &primes[i]);
    }
    fclose(fin);
    
    for (i = 0; i < TABLE_SIZE; ++i) {
        table[i] = -1;
    }
    while (count < N) {
        for (i = 0; i < K; ++i) {
            if (nth % primes[i] == 0 && (nth == primes[i] || exist(nth / primes[i]))) {
                set(nth);
                ++count;
                break;
            }
        }
        ++nth;
    }
    
    FILE *fout = fopen("humble.out", "w");
    fprintf(fout, "%d\n", nth - 1);
    fclose(fout);
    
    exit(0);
}
