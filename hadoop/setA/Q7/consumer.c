#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {

    int shmid;
    int *temp;

    shmid = shmget(1234, 5 * sizeof(int), 0666);

    temp = (int*) shmat(shmid, NULL, 0);

    printf("Temperature values:\n");

    for(int i = 0; i < 5; i++) {
        printf("%d ", temp[i]);
    }

    printf("\n");

    shmdt(temp);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}