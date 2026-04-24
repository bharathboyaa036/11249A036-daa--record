#include<stdio.h>
#include<limits.h>

int min_dist(int dist[], int visited[]);
void greedy_dijsktra(int graph[6][6], int src);

int min_dist(int dist[], int visited[])
{
    int minimum = INT_MAX;
    int ind = 0;
    int k;

    for(k = 0; k < 6; k++)
    {
        if(visited[k] == 0 && dist[k] <= minimum)
        {
            minimum = dist[k];
            ind = k;
        }
    }
    return ind;
}

void greedy_dijsktra(int graph[6][6], int src)
{
    int dist[6];
    int visited[6];
    int i, k, m;

    for(k = 0; k < 6; k++)
    {
        dist[k] = INT_MAX;
        visited[k] = 0;
    }

    dist[src] = 0;

    for(i = 0; i < 5; i++)
    {
        m = min_dist(dist, visited);
        visited[m] = 1;

        for(k = 0; k < 6; k++)
        {
            if(!visited[k] && graph[m][k] &&
               dist[m] != INT_MAX &&
               dist[m] + graph[m][k] < dist[k])
            {
                dist[k] = dist[m] + graph[m][k];
            }
        }
    }

    printf("Vertex\tDistance from Source\n");

    for(k = 0; k < 6; k++)
    {
        printf("%c\t%d\n", 65 + k, dist[k]);
    }
}

int main()
{
    int graph[6][6] = {
        {0,1,2,0,0,0},
        {1,0,0,5,1,0},
        {2,0,0,2,3,0},
        {0,5,2,0,2,2},
        {0,1,3,2,0,1},
        {0,0,0,2,1,0}
    };

    greedy_dijsktra(graph,0);

    return 0;
}
