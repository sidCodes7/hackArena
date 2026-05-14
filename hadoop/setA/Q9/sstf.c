#include <stdio.h>
#include <stdlib.h>

int main() {

    int req[] = {98,183,37,122,14,124,65,67};
    int visited[8] = {0};

    int head = 53;
    int total = 0;

    printf("Order of servicing:\n");

    for(int i = 0; i < 8; i++) {

        int min = 9999;
        int index = -1;

        for(int j = 0; j < 8; j++) {

            if(!visited[j]) {

                int dist = abs(head - req[j]);

                if(dist < min) {
                    min = dist;
                    index = j;
                }
            }
        }

        visited[index] = 1;

        printf("%d ", req[index]);

        total += abs(head - req[index]);

        head = req[index];
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}