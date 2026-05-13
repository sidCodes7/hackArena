#include <stdio.h>
#include <time.h>

void insertionSort(int arr[], int n){
    int i, key, j;
    for(int i = 1; i<n; i++){
        key = arr[i];
        j = i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }

}

void selectionSort(int arr[], int n){
    int i, min_idx, j, temp;
    for(i = 0; i<n-1; i++){
        min_idx = i;
        for(j = i+1; j<n; j++){
            if(arr[j]<arr[min_idx]){
                min_idx = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void copyArray(int src[], int dest[], int n) {
    for(int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n], arr1[n], arr2[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    copyArray(arr, arr1, n);
    copyArray(arr, arr2, n);
    
    clock_t start, end;
    start = clock();
    insertionSort(arr1, n);
    end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    
    printf("\nInsertion Sort Result:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\nTime taken: %f ms\n", time_taken);
    

    start = clock();
    selectionSort(arr2, n);
    end = clock();
    
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("\nSelection Sort Results:\n");
    for(int i = 0; i<n; i++){
        printf("%d ", arr2[i]);
    }
    printf("\nTime Taken: %f ms\n", time_taken);
    return 0;
}