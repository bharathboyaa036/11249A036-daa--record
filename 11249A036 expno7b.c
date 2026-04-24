#include <stdio.h>
#include <stdlib.h>

#define MAX 10   // maximum vertices

// Comparator for qsort
int comparator(const void *a, const void *b)
{
    int *x = (int *)a;
    int *y = (int *)b;
    return x[2] - y[2];
}

// Initialize sets
void makeSet(int parent[], int rank[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Find parent with path compression
int findParent(int parent[], int x)
{
    if (parent[x] != x)
        parent[x] = findParent(parent, parent[x]);
    return parent[x];
}

// Union by rank
void unionSet(int u, int v, int parent[], int rank[])
{
    if (rank[u] < rank[v])
        parent[u] = v;
    else if (rank[u] > rank[v])
        parent[v] = u;
    else {
        parent[v] = u;
        rank[u]++;
    }
}

// Kruskal Algorithm
int kruskalAlgo(int vertices, int edges, int edgeList[][3])
{
    int parent[MAX], rank[MAX];
    int i, minCost = 0;

    qsort(edgeList, edges, sizeof(edgeList[0]), comparator);

    makeSet(parent, rank, vertices);

    for (i = 0; i < edges; i++) {
        int u = edgeList[i][0];
        int v = edgeList[i][1];
        int wt = edgeList[i][2];

        int setU = findParent(parent, u);
        int setV = findParent(parent, v);

        if (setU != setV) {
            unionSet(setU, setV, parent, rank);
            minCost += wt;
        }
    }

    return minCost;
}

// Driver code
int main()
{
    int edge[5][3] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    int vertices = 4;
    int edges = 5;

    printf("Minimum Cost: %d\n", kruskalAlgo(vertices, edges, edge));

    return 0;
}
