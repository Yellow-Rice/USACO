/*
 ID: philipy1
 LANG: C
 TASK: runround
 */

/*
 *This program works because no runaround
 *number greater than 1E8. It cannot search
 *all numbers less than 1E10 in 60s, in fact.
 *we can use permutation to enumerate all
 *numbers that have a unique digit other
 *than 0 to potentially reduce cases.
 */

#include <stdio.h>
#include <stdlib.h>

_Bool isRunaround(unsigned i);
int flags[10] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int digits[9];

unsigned M;

int main()
{
	FILE *fin = fopen("runround.in", "r");
	fscanf(fin, "%u", &M);
	fclose(fin);
	
	unsigned i, count = 0;
	
	FILE *fout = fopen("runround.out", "w");
	for (i = M + 1; i < 1000000000; ++i) {
		//printf("***");
		if (isRunaround(i)) {
			//++count;
			//printf("Runaround Number %u: %u\n", count, i);
			fprintf(fout, "%d\n", i);
			break;
		}
		/*if (0 == i % 1000000) {
			printf("i = %d\n", i);
		}*/
	}
	//printf("count = %u\n", count);
	fclose(fout);
	
	exit(0);
}

_Bool isRunaround(unsigned n)
{
	int i, temp = n, count = 0, index = 0;
	for (i = 1; i < 10; ++i) {
		flags[i] = 0;
	}
	while (temp) {
		if (flags[temp % 10]) {
			return 0;
		}
		flags[temp % 10] = 1;
		temp /= 10;
		++count;
	}
	
	for (i = count - 1, temp = n; i >= 0; --i, temp /= 10) {
		digits[i] = temp % 10;
	}
	
	for (i = 0, temp = digits[0]; i < count; ++i, temp = digits[index]) {
		if (++flags[digits[index = (temp + index) % count]] != 2)
			return 0;
	}
	return 1;
}
