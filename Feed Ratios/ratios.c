/*
 ID: philipy1
 LANG: C
 TASK: ratios
 */
 
#include <stdio.h>
#include <stdlib.h>

inline int gcd(int i, int j)
{
    if (i < 0 || j < 0) {
        return -1;
    }
    if (i == 0) {
        return j;
    }
    if (j == 0) {
        return i;
    }
	
    int r = 1;
    while (r) {
        r = i % j;
        i = j;
        j = r;
    }
	return i;
}

int main()
{
    int m[3]; //mixture ratio
    int f[3][3]; //feeds ratio
    int n1, n2, n3, n0;
    int divisor;
    FILE *fin = fopen("ratios.in", "r");
    fscanf(fin, "%d %d %d", &m[0], &m[1], &m[2]);
    fscanf(fin, "%d %d %d", &f[0][0], &f[0][1], &f[0][2]);
    fscanf(fin, "%d %d %d", &f[1][0], &f[1][1], &f[1][2]);
    fscanf(fin, "%d %d %d", &f[2][0], &f[2][1], &f[2][2]);
    fclose(fin);
    
    n1 = +f[1][0] * f[2][1] * m[2] - f[1][0] * f[2][2] * m[1] - f[1][1] * f[2][0] * m[2] \
        + f[1][1] * f[2][2] * m[0] + f[1][2] * f[2][0] * m[1] - f[1][2] * f[2][1] * m[0];
    n2 = -f[0][0] * f[2][1] * m[2] + f[0][0] * f[2][2] * m[1] + f[0][1] * f[2][0] * m[2] \
        - f[0][1] * f[2][2] * m[0] - f[0][2] * f[2][0] * m[1] + f[0][2] * f[2][1] * m[0];
    n3 = +f[0][0] * f[1][1] * m[2] - f[0][0] * f[1][2] * m[1] - f[0][1] * f[1][0] * m[2] \
        + f[0][1] * f[1][2] * m[0] + f[0][2] * f[1][0] * m[1] - f[0][2] * f[1][1] * m[0];
    n0 = +f[0][0] * f[1][1] * f[2][2] - f[0][0] * f[1][2] * f[2][1] - f[0][1] * f[1][0] * f[2][2] \
        + f[0][1] * f[1][2] * f[2][0] + f[0][2] * f[1][0] * f[2][1] - f[0][2] * f[1][1] * f[2][0];
    
    FILE *fout = fopen("ratios.out", "w");
    /* 
     *criteria below out of range
     *if (n1 * n2 < 0 || n1 * n3 < 0 || n1 * n0 < 0 || n2 * n3 < 0 || n2 * n0 < 0 || n3 * n0 < 0) {
     */
    if (!(n1 >= 0 && n2 >= 0 && n3 >= 0 && n0 >= 0) && !(n1 <= 0 && n2 <= 0 && n3 <= 0 && n0 <= 0)) {
        fprintf(fout, "NONE\n");
        fclose(fout);
        exit(0);
    }
    if (n1 < 0 || n2 < 0 || n3 < 0 || n0 < 0) {
        n1 = -n1;
        n2 = -n2;
        n3 = -n3;
        n0 = -n0;
    }
    divisor = gcd(n0, n1);
    divisor = gcd(divisor, n2);
    divisor = gcd(divisor, n3);
    n1 /= divisor;
    n2 /= divisor;
    n3 /= divisor;
    n0 /= divisor;
    fprintf(fout, "%d %d %d %d\n", n1, n2, n3, n0);
    fclose(fout);
    
    exit(0);
}
