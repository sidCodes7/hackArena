#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

void generateGraph(int graph[MAX][MAX], int V) {

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }

    for(int i = 0; i < V; i++) {
        for(int j = i + 1; j < V; j++) {

            int edge = rand() % 2;

            graph[i][j] = edge;
            graph[j][i] = edge;
        }
    }
}

void vertexCover(int graph[MAX][MAX], int V) {

    int visited[MAX] = {0};

    printf("\nApproximate Vertex Cover:\n");

    for(int u = 0; u < V; u++) {

        if(visited[u] == 0) {

            for(int v = 0; v < V; v++) {

                if(graph[u][v] && visited[v] == 0) {

                    visited[u] = 1;
                    visited[v] = 1;

                    printf("%d ", u);
                    printf("%d ", v);

                    break;
                }
            }
        }
    }

    printf("\n");
}

int main() {

    int V;

    printf("Enter number of vertices (at least 20): ");
    scanf("%d", &V);

    int graph[MAX][MAX];

    srand(time(NULL));

    generateGraph(graph, V);

    printf("\nGenerated Graph (Adjacency Matrix):\n");

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    clock_t start, end;

    start = clock();

    vertexCover(graph, V);

    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("\nTime taken: %f ms\n", time_taken);

    return 0;
}