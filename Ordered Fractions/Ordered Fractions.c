/*
 ID: philipy1
 LANG: C
 TASK: frac1
 */
#include <stdio.h>
#include <stdlib.h>

void quick_sort(int _first, int _last);
inline int gcd(int i, int j);
inline int fraction_compare(int a, int b);

int numerators[1000000];
int denominators[1000000];
int size = 0;

int main()
{
	int N, i, j;
	FILE *fin = fopen("frac1.in", "r");
	fscanf(fin, "%d", &N);
	fclose(fin);
	
	for (i = 2; i <= N; ++i) {
		for (j = 1; j < i; ++j) {
			if (gcd(i, j) == 1) {
				numerators[size] = j;
				denominators[size++] = i;
			}
		}
	}
	
	quick_sort(0, size - 1);
	
	FILE *fout = fopen("frac1.out", "w");
	fprintf(fout, "0/1\n");
	for (i = 0; i < size; ++i) {
		fprintf(fout, "%d/%d\n", numerators[i], denominators[i]);
	}
	fprintf(fout, "1/1\n");
	fclose(fout);
	
	exit(0);
}

void quick_sort(int _first, int _last)
{
	if (_first < _last) {
		numerators[size] = numerators[_first];
		denominators[size] = denominators[_first];
		int first = _first, last = _last;
		while (first < last) {
			while (first < last && fraction_compare(last, size) > 0) {
				--last;
			}
			if (first < last) {
				numerators[first] = numerators[last];
				denominators[first++] = denominators[last];
			}
			while (first < last && fraction_compare(size, first) > 0) {
				++first;
			}
			if (first < last) {
				numerators[last] = numerators[first];
				denominators[last--] = denominators[first];
			}
		}
		numerators[first] = numerators[size];
		denominators[first] = denominators[size];
		
		quick_sort(_first, first - 1);
		quick_sort(first + 1, _last);
	}
}

inline int gcd(int i, int j)
{
	int r = 1;
	while (r) {
		r = i % j;
		i = j;
		j = r;
	}
	return i;
}

inline int fraction_compare(int a, int b)
{
	return numerators[a] * denominators[b] - numerators[b] * denominators[a];
}
