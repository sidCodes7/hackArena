#include <stdio.h>
#include <time.h>

#define MAX 100

struct Item{
    int profit, weight;
    float ratio;
};

void sortItems(struct Item items[], int n){

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n-i-1; j++){
            if(items[j].ratio<items[j+1].ratio){
                struct Item temp = items[j];
                items[j] = items[j+1];
                items[j+1] = temp;
            }
        }
    }
}

void fractionalKnapsack(struct Item items[], int n, int capacity){
    sortItems(items, n);

    float totalProfit = 0.0;

    printf("\nSelected items:\n");
    for(int i = 0; i<n; i++){
        if(items[i].weight<=capacity){
            capacity-=items[i].weight;
            totalProfit+=items[i].profit;

            printf("Item %d taken completely\n", i + 1);
        } else {
            float fraction = ((float)(capacity))/items[i].weight;
            totalProfit+= items[i].profit*fraction;
            printf("Item %d taken %.2f fraction\n", i + 1, fraction);
            break;
        }
    }

    printf("max profit:%f\n", totalProfit);
}

int main() {

    int n, capacity;

    struct Item items[MAX];

    printf("Enter number of items: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter profit and weight of item %d: ", i + 1);
        scanf("%d %d", &items[i].profit, &items[i].weight);

        items[i].ratio = (float)items[i].profit / items[i].weight;
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    clock_t start, end;

    start = clock();

    fractionalKnapsack(items, n, capacity);

    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("Time taken: %f ms\n", time_taken);

    return 0;
}