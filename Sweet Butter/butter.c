/*
 ID: philipy1
 LANG: C
 TASK: butter
 */

/*
 *Complexity: Adjacent list:(V + E) * V * log(V),   Adjacent matrix: (V^3)log(V)
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
    int p;
    int w;
    struct node *next;
};

int queue[801];
int size;
int cost[801];
int state[801]; // -1:visited, 0:Infinity, >0: position in heap

void percolate_up(int hole)
{
    int index, temp = queue[hole];
    for (index = hole; index > 1 && cost[queue[index / 2]] > cost[temp]; index /= 2) {
        queue[index] = queue[index / 2];
        state[queue[index]] = index;
    }
    queue[index] = temp;
    state[temp] = index;
}

void push(int n)
{
    queue[++size] = n;
    percolate_up(size);
}

int pop()
{
    if (size == 1) {
        state[queue[1]] = -1;
        return queue[size--];
    }

    int retval = queue[1];
    state[retval] = -1;
    int index, next;
    for (index = 1; index * 2 < size; index = next) {
        next = index * 2;
        if (size - 1 > next && cost[queue[next + 1]] < cost[queue[next]]) {
            ++next;
        }
        if (cost[queue[size]] > cost[queue[next]]) {
            queue[index] = queue[next];
            state[queue[index]] = index;
        }
        else {
            break;
        }
    }
    queue[index] = queue[size--];
    state[queue[index]] = index;
    return retval;
}

int main()
{
    int N, P, C;
    int dist[801][801];
    int path[801][801];
    struct node *head[801];
    struct node *tail[801];
    int pasture[801];
    int cow[1451];
    int i, j, k;
    int start, end, weight;
    int sum, min, min_cost;
    FILE *fin = fopen("butter.in", "r");
    fscanf(fin, "%d %d %d", &N, &P, &C);
    for (i = 1; i <= P; ++i) {
        for (j = 1; j < i; ++j) {
            dist[i][j] = dist[j][i] = INT_MAX;
        }
        dist[i][i] = 0;
    }
    for (i = 1; i <= P; ++i) {
        pasture[i] = 0;
        head[i] = tail[i] = NULL;
    }
    for (i = 1; i <= N; ++i) {
        fscanf(fin, "%d", &cow[i]);
        ++pasture[cow[i]];
    }
    for (i = 1; i <= C; ++i) {
        fscanf(fin, "%d %d %d", &start, &end, &weight);
        dist[start][end] = dist[end][start] = weight;
        if (!head[start]) {
            head[start] = malloc(sizeof(struct node));
            tail[start] = head[start];
        }
        else {
            tail[start] -> next = malloc(sizeof(struct node));
            tail[start] = tail[start] -> next;
        }
        tail[start] -> p = end;
        tail[start] -> w = weight;
        tail[start] -> next = NULL;
        if (!head[end]) {
            head[end] = malloc(sizeof(struct node));
            tail[end] = head[end];
        }
        else {
            tail[end] -> next = malloc(sizeof(struct node));
            tail[end] = tail[end] -> next;
        }
        tail[end] -> p = start;
        tail[end] -> w = weight;
        tail[end] -> next = NULL;
    }
    fclose(fin);
    
    //Implement Dijkstra's algorithm with priority queue for every vertex
    min_cost = INT_MAX;
    struct node *nd;
    for (i = 1; i <= P; ++i) {
        sum = 0;
        for (j = 1; j <= P; ++j) {
            cost[j] = INT_MAX;
            state[j] = 0;
        }
        cost[i] = 0;
        size = 0;
        push(i);
        while (size) {
            min = pop();
            for (nd = head[min]; nd; nd = nd -> next) {
                if (state[nd -> p] == 0) {
                    cost[nd -> p] = cost[min] + nd -> w;
                    push(nd -> p);
                }
                else if (state[nd -> p] > 0 && cost[min] + nd -> w < cost[nd -> p]) {
                    cost[nd -> p] = cost[min] + nd -> w;
                    percolate_up(state[nd -> p]);
                }
            }
            //Codes below is very slow...
            /*for (j = 1; j <= P; ++j) {
                if (state[j] == 0 && dist[min][j] < INT_MAX) {
                    cost[j] = cost[min] + dist[min][j];
                    push(j);
                }
                else if (state[j] > 0 && dist[min][j] < INT_MAX && cost[min] + dist[min][j] < cost[j]) {
                    cost[j] = cost[min] + dist[min][j];
                    percolate_up(state[j]);
                }
            }*/
        }
        for (j = 1; j <= P && (pasture[j] == 0 || cost[j] < INT_MAX); ++j) {
                sum += (pasture[j] * cost[j]);
        }
        if (sum < min_cost && j > P) {
            min_cost = sum;
        }
    }
    
    FILE *fout = fopen("butter.out", "w");
    fprintf(fout, "%d\n", min_cost);
    fprintf(stdout, "%d\n", min_cost);
    fclose(fout);
    
    exit(0);
}
