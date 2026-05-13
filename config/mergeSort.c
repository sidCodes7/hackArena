#include <stdio.h>
#include <time.h>
void merge(int arr[], int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int l[n1], r[n2];

    for(int i = 0; i<n1; i++){
        l[i] = arr[left+i];
    }

    for(int i = 0; i<n2; i++){
        r[i] = arr[mid+1+i];
    }

    int i = 0, j = 0, k = left;
    
    while(i<n1 && j<n2){
        if(l[i]<=r[j]){
            arr[k] = l[i];
            i++;
        } else {
            arr[k] = r[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = l[i];
        i++, k++;
    }

    while(j<n2){
        arr[k] = r[j];
        j++, k++;
    }
}

void mergeSort(int arr[], int left, int right){
    if(left<right){
        int mid = left + (right-left)/2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);

        merge(arr, left, mid, right);
    }
}

int main(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    clock_t start, end;
    start = clock();
    mergeSort(arr, 0, n-1);
    end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("the sorted arr:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nTime taken: %f ms", time_taken);

    return 0;
}