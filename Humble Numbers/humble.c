/*
 ID: philipy1
 LANG: C
 TASK: humble
 */
 
/*
 *We compute the first n humble numbers in the "hum" array. For simplicity of implementation, we treat 1 as a humble number, and adjust accordingly.
 *Once we have the first k humble numbers and want to compute the k+1st, we do the following:
 *
 *for each prime p
 *  find the minimum humble number h
 *      such that h * p is bigger than the last humble number.
 *take the smallest h * p found: that's the next humble number.
 *
 *To speed up the search, we keep an index "pindex" of what h is for each prime, and start there rather than at the beginning of the list. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int split(int arr[], int first, int last)
{
    int hole = arr[first];
    while (first < last) {
        while (first < last && arr[last] >= hole) --last;
        if (first < last) arr[first++] = arr[last];
        while (first < last && arr[first] <= hole) ++first;
        if (first < last) arr[last++] = arr[first];
    }
    arr[first] = hole;
    return first;
}

void quick_sort(int arr[], int first, int last)
{
    if (first < last) {
        int mid = split(arr, first, last);
        quick_sort(arr, first, mid - 1);
        quick_sort(arr, mid + 1, last);
    }
}

int main()
{
    int K, N;
    int primes[100];
    int humbles[100001] = {1};
    int pindex[100];
    //int hindex = 0;
    int min = 2, temp;
    int i, j, k;
    FILE *fin = fopen("humble.in", "r");
    fscanf(fin, "%d %d", &K, &N);
    for (i = 0; i < K; ++i) {
        fscanf(fin, "%d", &primes[i]);
    }
    fclose(fin);
    
    //quick_sort(primes, 0, K - 1);
    for (i = 0; i <= K; ++i) {
        pindex[i] = 0;
    }
    
    for (i = 1; i <= N; ++i) {
        min = INT_MAX;
        for (j = 0; j < K; ++j) {
            for (k = pindex[j]; k < i; ++k) {
                if ((temp = humbles[k] * primes[j]) > humbles[i - 1]) {
                    if (temp < min) {
                        min = temp;
                    }
                    pindex[j] = k;
                    break;
                }
            }
            if (k == i) {
                pindex[j] = i;
            }
        }
        humbles[i] = min;
    }
    
    FILE *fout = fopen("humble.out", "w");
    fprintf(fout, "%d\n", humbles[N]);
    fclose(fout);
    
    exit(0);
}
