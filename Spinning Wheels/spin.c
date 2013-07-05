/*
 ID: philipy1
 LANG: C
 TASK: spin
 */
 
#include <stdio.h>
#include <stdlib.h>

inline int gcd(int i, int j)
{
    if (i < 0 || j < 0) {
		return -1;
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
    int speed[5];
    int size[5];
    int w_start[5][5];
    int w_extent[5][5];
    int flags[360];
    int i, j, k, l;
    int period = 360;
    _Bool flag;
    FILE *fin = fopen("spin.in", "r");
    for (i = 0; i < 5; ++i) {
        fscanf(fin, "%d %d", &speed[i], &size[i]);
        for (j = 0; j < size[i]; ++j) {
            fscanf(fin, "%d %d", &w_start[i][j], &w_extent[i][j]);
        }
        period = gcd(speed[i], period);
    }
    fclose(fin);
    
    period = 360 / period;
    flag = 0;
    for (i = 0; !flag && i < period; ++i) {
        for (j = 0; j < 360; ++j) {
            flags[j] = 0;
        }
        for (j = 0; j < 5; ++j) {
            for (k = 0; k < size[j]; ++k) {
                for (l = w_start[j][k]; l <= (w_start[j][k] + w_extent[j][k]); ++l) {
                    ++flags[(speed[j] * i + l) % 360];
                }
            }
        }
        for (j = 0; j < 360; ++j) {
            if (flags[j] == 5) {
                flag = 1;
                --i;
                break;
            }
        }
    }
    
    FILE *fout = fopen("spin.out", "w");
    if (i == period) {
        fprintf(fout, "none\n");
    }
    else {
        fprintf(fout, "%d\n", i);
    }
    fclose(fout);
    
    exit(0);
}
