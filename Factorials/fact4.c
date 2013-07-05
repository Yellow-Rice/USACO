/*
 ID: philipy1
 LANG: C
 TASK: fact4
 */
 
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    int reminders[10][10];
    int ans;
    int count5;
    int i, j;
    int temp;
    FILE *fin = fopen("fact4.in", "r");
    fscanf(fin, "%d", &N);
    fclose(fin);
    
    for (i = 0; i < 10; ++i) {
        for (j = 0; j < 10; ++j) {
            reminders[i][j] = (i * j) % 10;
        }
    }
    count5 = 0;
    count5 += ((N + 5) / 10 + (N + 25) / 50 + (N + 125) / 250 + (N + 625) / 1250 + (N + 3125) / 6250);
    count5 += ((N + 50) / 100 + (N + 250) / 500 + (N + 1250) / 2500);
    count5 += ((N + 500) / 1000 + (N + 2500) / 5000);
    ans = 1;
    for (i = 2; i <= N; ++i) {
        temp = i;
        while (temp % 10 == 0) {
            temp /= 10;
        }
        while (temp % 5 == 0) {
            temp /= 5;
        }
        while (count5 && temp % 2 == 0) {
            --count5;
            temp >>= 1;
        }
        if (temp % 5) {
            ans = reminders[ans][temp % 10];
        }
    }
    
    FILE *fout = fopen("fact4.out", "w");
    fprintf(fout, "%d\n", ans);
    fclose(fout);
    
    exit(0);
}
