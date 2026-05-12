#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    char buffer[1024];

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    printf("Connected! Type your message below:\n");

    if (fork() == 0) {
        // Child: Continuously receive
        while (recv(sock, buffer, 1024, 0) > 0) {
            printf("\nOther: %s", buffer);
            memset(buffer, 0, 1024);
        }
    } else {
        // Parent: Continuously send
        while (1) {
            fgets(buffer, 1024, stdin);
            send(sock, buffer, strlen(buffer), 0);
            if (strncmp(buffer, "exit", 4) == 0) break;
        }
    }

    close(sock);
    return 0;
}