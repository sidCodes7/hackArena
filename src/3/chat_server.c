#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

int clients[2];

void *handle_relay(void *arg) {
    int index = *(int *)arg;
    int src = clients[index];
    int dest = clients[1 - index]; 
    char buffer[1024];
    int n;

    while ((n = recv(src, buffer, sizeof(buffer), 0)) > 0) {
        send(dest, buffer, n, 0); // Relay the message exactly as received 
        memset(buffer, 0, 1024);
    }
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)); 
    listen(server_fd, 2); 
    printf("Chat Server waiting for 2 clients...\n");

    for (int i = 0; i < 2; i++) {
        clients[i] = accept(server_fd, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
        printf("Client %d connected.\n", i + 1);
    }

    pthread_t t1, t2;
    int idx0 = 0, idx1 = 1;
    pthread_create(&t1, NULL, handle_relay, &idx0);
    pthread_create(&t2, NULL, handle_relay, &idx1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    close(server_fd); 
    return 0;
}