#include <stdio.h>

int main() {
    int n = 4, r = 2;

    int alloc[4][2] = {
        {1,0},
        {1,1},
        {1,0},
        {0,1}
    };

    int max[4][2] = {
        {2,1},
        {1,2},
        {1,1},
        {1,2}
    };

    // Total resources:
    // Printers = 3
    // Scanners = 4

    // Allocated:
    // Printers = 3
    // Scanners = 2

    // Available = Total - Allocated
    int avail[2] = {0,2};

    int need[4][2];
    int finish[4] = {0};
    int safe[4];
    int count = 0;

    // Calculate Need matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    while(count < n) {

        int found = 0;

        for(int i = 0; i < n; i++) {

            if(finish[i] == 0) {

                int possible = 1;

                for(int j = 0; j < r; j++) {
                    if(need[i][j] > avail[j]) {
                        possible = 0;
                        break;
                    }
                }

                if(possible) {

                    for(int j = 0; j < r; j++) {
                        avail[j] += alloc[i][j];
                    }

                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("System is in deadlock\n");
            return 0;
        }
    }

    printf("Safe sequence: ");

    for(int i = 0; i < n; i++) {
        printf("P%d ", safe[i]);
    }

    printf("\n");

    return 0;
}