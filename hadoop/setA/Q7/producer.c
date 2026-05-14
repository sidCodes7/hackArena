#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {

    int shmid;
    int *temp;

    int values[5] = {30, 32, 31, 29, 33};

    shmid = shmget(1234, 5 * sizeof(int), 0666 | IPC_CREAT);

    temp = (int*) shmat(shmid, NULL, 0);

    for(int i = 0; i < 5; i++) {
        temp[i] = values[i];
    }

    printf("Temperature values written\n");

    shmdt(temp);

    return 0;
}