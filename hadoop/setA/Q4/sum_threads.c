#include <stdio.h>
#include <pthread.h>

int arr[100];
int part_sum[4];

void* sum(void* arg){
    int part = *(int*)arg;
    int start = part*25;
    int end = start+25;

    part_sum[part] = 0;

    for(int i = start; i<end; i++){
        part_sum[part]+=arr[i];
    }

    return NULL;
}

int main(){
    pthread_t t[4];
    int part[4];
    int total = 0;

    for(int i = 0; i < 100; i++)
        arr[i] = i + 1;

    for(int i = 0; i<4; i++){
        part[i] = i;
        pthread_create(&t[i], NULL, sum, &part[i]);
    }

    for(int i = 0; i<4; i++){
        pthread_join(t[i], NULL);
    }

    for(int i = 0; i<4; i++){
        total+=part_sum[i];
    }

    printf("Total Sum = %d\n", total);

    return 0;
}