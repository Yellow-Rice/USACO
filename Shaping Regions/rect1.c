/*
 ID: philipy1
 LANG: C
 TASK: rect1
 */
 
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 700000
int llxs[ARR_SIZE], llys[ARR_SIZE], urxs[ARR_SIZE], urys[ARR_SIZE], colors[ARR_SIZE];
int count = 0;

inline void insert(int llx, int lly, int urx, int ury, int color)
{
    while (colors[count]) {
        count = (count + 1) % ARR_SIZE;
    }
    
    llxs[count] = llx;
    llys[count] = lly;
    urxs[count] = urx;
    urys[count] = ury;
    colors[count] = color;
    count = (count + 1) % ARR_SIZE;
}

inline void del(int i)
{
    colors[i] = 0;
}

int main()
{
    int A, B, N;
    int results[2501];
    int llx, lly, urx, ury, color;
    int lx, ly, rx, ry;
    int i, j, k;
    int temp;
    
    for (i = 0; i < ARR_SIZE; ++i) {
        colors[i] = 0;
    }
    
    FILE *fin = fopen("rect1.in", "r");
    fscanf(fin, "%d %d %d", &A, &B, &N);
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%d %d %d %d %d", &llx, &lly, &urx, &ury, &color);
        for (j = 0; j < ARR_SIZE; ++j) {
            if (!colors[j]) {
                continue;
            }
            lx = llx > llxs[j] ? llx : llxs[j];
            ly = lly > llys[j] ? lly : llys[j];
            rx = urx < urxs[j] ? urx : urxs[j];
            ry = ury < urys[j] ? ury : urys[j];
            if (lx < rx && ly < ry) {
                if (lx > llxs[j]) {
                    insert(llxs[j], llys[j], lx, urys[j], colors[j]);/*
                    llxs[count] = llxs[j];
                    llys[count] = llys[j];
                    urxs[count] = lx;
                    urys[count] = urys[j];
                    colors[count++] = colors[j];*/
                }
                if (ly > llys[j]) {
                    insert(lx, llys[j], rx, ly, colors[j]);/*
                    llxs[count] = lx;
                    llys[count] = llys[j];
                    urxs[count] = rx;
                    urys[count] = ly;
                    colors[count++] = colors[j];*/
                }
                if (rx < urxs[j]) {
                    insert(rx, llys[j], urxs[j], urys[j], colors[j]);/*
                    llxs[count] = rx;
                    llys[count] = llys[j];
                    urxs[count] = urxs[j];
                    urys[count] = urys[j];
                    colors[count++] = colors[j];*/
                }
                if (ry < urys[j]) {
                    insert(lx, ry, rx, urys[j], colors[j]);/*
                    llxs[count] = lx;
                    llys[count] = ry;
                    urxs[count] = rx;
                    urys[count] = urys[j];
                    colors[count++] = colors[j];*/
                }
                colors[j] = 0;
                //del(j);
            }
        }
        insert(llx, lly, urx, ury, color);/*
        llxs[count] = llx;
        llys[count] = lly;
        urxs[count] = urx;
        urys[count] = ury;
        colors[count++] = color;*/
    }
    fclose(fin);
    
    results[1] = A * B;
    for (i = 2; i < 2501; ++i) {
        results[i] = 0;
    }
    for (i = 0; i < count; ++i) {
        if (colors[i]) {
            temp = (urxs[i] - llxs[i]) * (urys[i] - llys[i]);
            results[colors[i]] += temp;
            results[1] -= temp;
        }
    }
    
    FILE *fout = fopen("rect1.out", "w");
    for (i = 1; i < 2501; ++i) {
        if (results[i]) {
            fprintf(fout, "%d %d\n", i, results[i]);
        }
    }
    fclose(fout);
    
    exit(0);
}
