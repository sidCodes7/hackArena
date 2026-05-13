#include <stdio.h>
#include <time.h>

#define MAX 100

int max(int a, int b){
    return (a>b)?a:b;
}

int knapsack(int C, int wt[], int val[], int n){
    int k[MAX][MAX];

    for(int i = 0; i<=n; i++){
        for(int w = 0; w<=C; w++){
            if(w==0 || i == 0){
                k[i][w] = 0;
            } else if(wt[i-1]<=w){
                k[i][w] = max(val[i-1] + k[i-1][w-wt[i-1]], k[i-1][w]);
            } else {
                k[i][w] = k[i-1][w];
            }
        }
    }

    int i = n;
    int w = C;

    while(i>0 && w>0){
        if(k[i][w]!=k[i-1][w]){
            printf("%d item included\n", i);
            w = w - wt[i-1];
        } else {
            printf("%d item not included\n", i);
        }
        i--;
    }

    while(i>0){
        printf("Item %d not included\n", i);
        i--;
    }

    return k[n][C];
}

int main() {

    int n, W;

    int wt[MAX], val[MAX];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter profits of items:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }

    printf("Enter weights of items:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &wt[i]);
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    clock_t start, end;

    start = clock();

    int result = knapsack(W, wt, val, n);

    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("\nMaximum Profit = %d\n", result);

    printf("Time taken: %f ms\n", time_taken);

    return 0;
}