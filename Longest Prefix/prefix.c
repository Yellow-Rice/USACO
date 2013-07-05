/*
 ID: philipy1
 LANG: C
 TASK: prefix
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char primitives[26][100][11], S[200001], temp[77];
int flags[200001] = {1};
int pri_count[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int length;

int main()
{
	FILE *fin = fopen("prefix.in", "r");
	int i, j, index, l;
	fscanf(fin, "%s", S);
	while (strcmp(S, ".")) {
		strcpy(primitives[S[0] - 'A'][pri_count[S[0] - 'A']++], S);
		fscanf(fin, "%s", S);
	}
    S[0] = '\0';
	while (1 == fscanf(fin, "%s", temp)) {
        strcat(S, temp);
	}
    length = strlen(S);
	fclose(fin);

    for (i = 1; i <= length; ++i) {
        flags[i] = 0;
    }
    for (i = 0; i < length; ++i ) {
        for (j = 0, index = S[i] - 'A'; flags[i] && j < pri_count[index]; ++j) {
            if (i + (l = strlen(primitives[index][j])) <= length && 0 == strncmp(S + i, primitives[index][j], l)) {
                flags[i + l] = 1;
            }
        }
    }
    while (!flags[length--]) ;
    FILE *fout = fopen("prefix.out", "w");
    fprintf(fout, "%d\n", ++length);
    fclose(fout);

	exit(0);
}
