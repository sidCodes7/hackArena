#include <stdio.h>
#include <limits.h>
#include <time.h>

#define max 100

int minDist(int visted[], int dist[], int V){
    int min = INT_MAX;
    int min_idx;

    for(int v = 0; v<V; v++){
        if(visted[v]==0 && dist[v]<min){
            min = dist[v];
            min_idx = v;
        }
    }

    return min_idx;
}

void dijkstra(int graph[max][max], int V, int src){
    int dist[max];
    int visited[max];

    for(int i = 0; i<V; i++){
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[src] = 0;

    for(int c = 0; c<V-1; c++){
        int u = minDist(visited, dist, V);
        visited[u] = 1;

        for(int v = 0; v<V; v++){
            if(!visited[v] && graph[u][v] && dist[u]!=INT_MAX && graph[u][v]+dist[u]<dist[v]){
                dist[v] = graph[u][v]+dist[u];
            }
        }
    }

    for(int i = 0; i<V; i++){
        printf("%d\t\t%d\n", i, dist[i]);
    }
}

int main() {

    int V;
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    int graph[max][max];
    printf("Enter adjacency matrix:\n");
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int src;
    printf("Enter source vertex: ");
    scanf("%d", &src);

    clock_t start, end;
    start = clock();
    dijkstra(graph, V, src);
    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("\nTime taken: %f ms\n", time_taken);

    return 0;

}