/*
ID: philipy1
LANG: C
TASK: cowtour
*/
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

int N;
double matrix[150][150];
double pos_x[150], pos_y[150];
int pasture[150];
double diameter[150];

inline double dist(int i, int j)
{
    return sqrt((pos_x[i] - pos_x[j]) * (pos_x[i] - pos_x[j]) + (pos_y[i] - pos_y[j]) * (pos_y[i] - pos_y[j]));
}

inline int find(int n)
{
    while (pasture[n] >= 0) {
        n = pasture[n];
    }
    return n;
}

inline void merge(int m, int n)
{
    //printf("m = %d, n = %d\n", m, n);
    m = find(m);
    n = find(n);
    //printf("m = %d, n = %d\n", m, n);
    if (m != n) {
        pasture[m] += pasture[n];
        pasture[n] = m;
    }
}

int main()
{
    int i, j, k;
    double d, d1, d2, max1 = 0, max2 = 0,s;
    double min = DBL_MAX;
    FILE *fin = fopen("cowtour.in", "r");
    fscanf(fin, "%d\n", &N);
    for (i = 0; i < N; ++i) {
        fscanf(fin, "%lf %lf\n", &pos_x[i], &pos_y[i]);
        pasture[i] = -1;
    }
    for (i = 0; i < N; ++i) {
        for (j = 0; j < i; ++j) {
            //printf("i = %d, j = %d\n", i, j);
            if (fgetc(fin) - '0') {
                matrix[i][j] = matrix[j][i] = dist(i, j);
                merge(j, i);
            }
            else {
                matrix[i][j] = matrix[j][i]  = DBL_MAX;
            }
        }
        matrix[i][i] = DBL_MAX;
        while((k = fgetc(fin)) != '\n' && k != EOF) ;
    }
    fclose(fin);
    
    printf("reading finished!\n");
    
    for (i = 0; i < N; ++i) {
        /*for (j = 0; j < N; ++j) {
            printf("%d", matrix[i][j] == DBL_MAX ? 0 : 1);
        }
        printf("\n");*/
        /*if (matrix[i][104] != DBL_MAX) {
            printf("%d\t", i);
        }*/
        printf("%d\t", find(i));
    }
    printf("\n");
    
    //Floyd-warshall Algorithm start
    for (k = 0; k < N; ++k) {
        for (i = 0; i < N; ++i) {
            for (j = 0; j < i; ++j) {
                if (matrix[i][k] < DBL_MAX && matrix[k][j] < DBL_MAX && matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[j][i] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
    //Floyd-warshall Algorithm finish
    
    /*for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%.1lf\t", matrix[i][j] == DBL_MAX ? -1 : matrix[i][j]);
        }
        printf("\n");
    }*/
    
    //find the diameter of each pasture
    for (i = 0; i < N; ++i) {
        diameter[i] = 0;
    }
    for (i = 0; i < N; ++i) {
        for (j = 0; j < N; ++j) {
            if (matrix[i][j] < DBL_MAX && matrix[i][j] > diameter[k = find(j)]) {
                diameter[k] = matrix[i][j];
            }
        }
    }
    
    for (i = 0; i < N; ++i) {
        for (j = 0; j < i; ++j) {
            if (DBL_MAX == matrix[i][j]) {
                d1 = diameter[find(i)];
                d2 = diameter[find(j)];
                d = dist(i, j);
                max1 = 0;
                max2 = 0;
                for (k = 0; k < N; ++k) {
                    if (matrix[i][k] < DBL_MAX && max1 < matrix[i][k]) {
                        max1 = matrix[i][k];
                    }
                    if (matrix[k][j] < DBL_MAX && max2 < matrix[k][j]) {
                        max2 = matrix[k][j];
                    }
                }
                /*if (max1 == 0 || max2 == 0) {
                    continue;
                }*/
                printf("i=%d,\tj=%d,\tmax1=%.1lf,\tmax2=%.1lf,\td=%.1lf\n", i, j, max1, max2, d);
                max1 += (max2 + d);
                printf("max=%.1lf,\td1=%.1lf,\td2=%.1lf\n", max1, d1, d2);
                d1 = d1 > d2 ? d1 : d2;
                d1 = d1 > max1 ? d1 : max1;
                min = min < d1 ? min : d1;
                
                //min = min < max1 ? min : max1;
            }
        }
    }
    
    FILE *fout = fopen("cowtour.out", "w");
    fprintf(fout, "%.6lf\n", min);
    fclose(fout);
    
    exit(0);
}
