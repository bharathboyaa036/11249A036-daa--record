#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 6

int graph[MAX_VERTICES][MAX_VERTICES] = {
    {0,10,0,15,0,0},
    {0,0,0,5,10,0},
    {0,0,0,0,0,10},
    {0,0,0,0,0,5},
    {0,0,0,0,0,10},
    {0,0,0,0,0,0}
};

void bellman_ford(int source)
{
    int distance[MAX_VERTICES];
    int i, u, v;

    for(i = 0; i < MAX_VERTICES; i++)
        distance[i] = INT_MAX;

    distance[source] = 0;

    for(i = 0; i < MAX_VERTICES - 1; i++)
    {
        for(u = 0; u < MAX_VERTICES; u++)
        {
            for(v = 0; v < MAX_VERTICES; v++)
            {
                if(graph[u][v] != 0 && distance[u] != INT_MAX &&
                   distance[u] + graph[u][v] < distance[v])
                {
                    distance[v] = distance[u] + graph[u][v];
                }
            }
        }
    }

    for(u = 0; u < MAX_VERTICES; u++)
    {
        for(v = 0; v < MAX_VERTICES; v++)
        {
            if(graph[u][v] != 0 && distance[u] != INT_MAX &&
               distance[u] + graph[u][v] < distance[v])
            {
                printf("Graph contains negative weight cycle\n");
                return;
            }
        }
    }

    printf("Vertex\tDistance from Source\n");

    for(i = 0; i < MAX_VERTICES; i++)
    {
        if(distance[i] == INT_MAX)
            printf("%d\tINF\n", i);
        else
            printf("%d\t%d\n", i, distance[i]);
    }
}

int main()
{
    bellman_ford(0);
    return 0;
}
