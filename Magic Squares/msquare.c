/*
 ID: philipy1
 LANG: C
 TASK: msquare
 */
 
 /*
  *Building a tree for all states might be easier (when coding) than bfs.
  */
 
#include <stdio.h>
#include <stdlib.h>

int initial[2][4] = {{0, 1, 2, 3}, {7, 6, 5, 4}};
int state[2][4];
int target[2][4];
int queue[1000000];
int parent[1000000];
char path[1000000];
#define TABLE_SIZE 999983 //A prime number, 8! = 720 * 56 states in total
int table[TABLE_SIZE];
int first, last;

inline int convert(int arr[2][4])
{
    return (arr[0][0] << 0) + (arr[0][1] << 3) + (arr[0][2] << 6) + (arr[0][3] << 9) + (arr[1][3] << 12) \
        + (arr[1][2] << 15) + (arr[1][1] << 18) + (arr[1][0] << 21);
}

inline void rconvert(int i)
{
    state[0][0] = i % 8;
    i >>= 3;
    state[0][1] = i % 8;
    i >>= 3;
    state[0][2] = i % 8;
    i >>= 3;
    state[0][3] = i % 8;
    i >>= 3;
    state[1][3] = i % 8;
    i >>= 3;
    state[1][2] = i % 8;
    i >>= 3;
    state[1][1] = i % 8;
    i >>= 3;
    state[1][0] = i % 8;
}

_Bool exist(int i)
{
    int index;
    for (index = i % TABLE_SIZE; table[index] != -1 && table[index] != i; index = (index + 1) % TABLE_SIZE) ;
    return table[index] == i;
}

/*_Bool exist()
{
    int i = convert(state);
    int index;
    for (index = i % TABLE_SIZE; table[index] != -1 && table[index] != i; index = (index + 1) % TABLE_SIZE) ;
    return table[index] == i;
}*/

void set(int i)
{
    int index;
    for (index = i % TABLE_SIZE; table[index] != -1 && table[index] != i; index = (index + 1) % TABLE_SIZE) ;
    table[index] = i;
}

/*void set()
{
    int i = convert(state);
    int index;
    for (index = i % TABLE_SIZE; table[index] != -1 && table[index] != i; index = (index + 1) % TABLE_SIZE) ;
    table[index] = i;
}*/

/*_Bool success()
{
    return state[0][0] == target[0][0] && state[0][1] == target[0][1] && state[0][2] == target[0][2] && \
        state[0][3] == target[0][3] && state[1][3] == target[1][3] && state[1][2] == target[1][2] && \
        state[1][1] == target[1][1] && state[1][0] == target[1][0];
}*/

inline void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void A()
{
    swap(&state[0][0], &state[1][0]);
    swap(&state[0][1], &state[1][1]);
    swap(&state[0][2], &state[1][2]);
    swap(&state[0][3], &state[1][3]);
}

void B()
{
    int temp = state[0][3];
    state[0][3] = state[0][2];
    state[0][2] = state[0][1];
    state[0][1] = state[0][0];
    state[0][0] = temp;
    temp = state[1][3];
    state[1][3] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = state[1][0];
    state[1][0] = temp;
}

void C()
{
    int temp = state[0][1];
    state[0][1] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[0][2];
    state[0][2] = temp;
}

/*void rA()
{
    A();
}

void rB()
{
    int temp = state[0][0];
    state[0][0] = state[0][1];
    state[0][1] = state[0][2];
    state[0][2] = state[0][3];
    state[0][3] = temp;
    temp = state[1][0];
    state[1][0] = state[1][1];
    state[1][1] = state[1][2];
    state[1][2] = state[1][3];
    state[1][3] = temp;
}

void rC()
{
    int temp = state[0][1];
    state[0][1] = state[0][2];
    state[0][2] = state[1][2];
    state[1][2] = state[1][1];
    state[1][1] = temp;
}*/

_Bool bfs()
{
    int i;
    int temp, success = convert(target);
    for (i = 0; i < TABLE_SIZE; ++i) {
        table[i] = -1;
    }
    first = last = 0;
    path[last] = 0;
    parent[last] = -1;
    queue[last++] = convert(initial);
    while (first < last) {
        temp = queue[first];
        if (exist(temp)) {
            ++first;
            continue;
        }
        else {
            set(temp);
            if (temp == success) {
                return 1;
            }
            rconvert(temp);
            A();
            path[last] = 'A';
            parent[last] = first;
            queue[last++] = convert(state);
            rconvert(temp);
            B();
            path[last] = 'B';
            parent[last] = first;
            queue[last++] = convert(state);
            rconvert(temp);
            C();
            path[last] = 'C';
            parent[last] = first++;
            queue[last++] = convert(state);
        }
    }
    return 0;
}

int main()
{
    char ans[100000];
    int count;
    int i;
    FILE *fin = fopen("msquare.in", "r");
    fscanf(fin, "%d %d %d %d %d %d %d %d", &target[0][0], &target[0][1], &target[0][2], &target[0][3], &target[1][3], &target[1][2], &target[1][1], &target[1][0]);
    fclose(fin);
    
    target[0][0] -= 1;
    target[0][1] -= 1;
    target[0][2] -= 1;
    target[0][3] -= 1;
    target[1][3] -= 1;
    target[1][2] -= 1;
    target[1][1] -= 1;
    target[1][0] -= 1;
    
    FILE *fout = fopen("msquare.out", "w");
    if (bfs()) {
        ans[100000];
        for (count = 0; path[first]; first = parent[first], ++count) {
            ans[count] = path[first];
        }
        fprintf(fout, "%d", count);
        fprintf(stdout, "%d", count);
        if (0 == count) {
            fprintf(fout, "\n");
            fprintf(stdout, "\n");
        }
        for (i = 0; i < count; ++i) {
            if (i % 60 == 0) {
                fprintf(fout, "\n");
                fprintf(stdout, "\n");
            }
            fprintf(fout, "%c", ans[count - i - 1]);
            fprintf(stdout, "%c", ans[count - i - 1]);
        }
        fprintf(fout, "\n");
        fprintf(stdout, "\n");
    }
    else {
        fprintf(fout, "Failed!\n");
        fprintf(stdout, "Failed!\n");
    }
    fclose(fout);
    
    exit(0);
}
