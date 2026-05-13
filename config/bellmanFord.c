#include <stdio.h>
#include <limits.h>
#include <time.h>

#define max 100

struct Edge{
    int src, dst, weight;
};

void bellmanFord(struct Edge edges[], int V, int E, int src){
    int dist[max];

    for(int i = 0; i<V; i++){
        dist[i] = INT_MAX;
    }

    dist[src] = 0;

    for(int i = 0; i<V-1; i++){
        for(int j = 0; j<E; j++){

            int u = edges[j].src;
            int v = edges[j].dst;
            int w = edges[j].weight;

            if(dist[u]!=INT_MAX && dist[u]+w<dist[v]){
                dist[v] = dist[u]+w;
            }
        }
    }

    for(int j = 0; j<E; j++){

        int u = edges[j].src;
        int v = edges[j].dst;
        int w = edges[j].weight;

        if(dist[u]!=INT_MAX && dist[u]+w<dist[v]){
            printf("\nneg w cycle found\n");
            return;
        }
    }

    printf("Vertex\tdist frm src\n");
    for(int i = 0; i<V; i++){
        printf("%d\t%d\n", i, dist[i]);
    }
}

int main(){
    int V, E;

    printf("Enter the number of Edges and Vertices\n");
    scanf("%d", &E);
    scanf("%d", &V);
    
    struct Edge edges[max];
    printf("Enter source destination weight:\n");

    for(int i = 0; i<E; i++){
        scanf("%d %d %d", &edges[i].src, &edges[i].dst, &edges[i].weight);
    }

    int src;
    printf("Enter source vertex: ");
    scanf("%d", &src);

    clock_t start, end;
    start = clock();
    bellmanFord(edges, V, E, src);
    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    
    printf("\nTime taken: %f ms\n", time_taken);

    return 0;
}