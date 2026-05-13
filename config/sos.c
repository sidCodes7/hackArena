#include <stdio.h>
#include <time.h>

#define max 100

int subset[max];
int found = 0;

void sos(int set[], int n, int target, int currSum, int idx, int subsetSize){
    if(currSum==target){
        found = 1;
        printf("{");
        for(int i = 0; i<subsetSize; i++){
            printf("%d ", subset[i]);
        }
        printf("}\n");
        return;
    }

    if(idx==n || currSum>target){
        return;
    }

    subset[subsetSize] = set[idx];

    sos(set, n, target, currSum+set[idx], idx+1, subsetSize+1);
    sos(set, n, target, currSum, idx+1, subsetSize);
}

int main(){
    int n, target;
    int set[max];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &set[i]);
    }

    printf("Enter target sum: ");
    scanf("%d", &target);

    clock_t start, end;
    start = clock();
    printf("\nSubsets with sum %d are:\n", target);
    sos(set, n, target, 0, 0, 0);
    if(!found) {
        printf("No subset found\n");
    }
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    printf("\nTime taken: %f ms\n", time_taken);
    return 0;
}