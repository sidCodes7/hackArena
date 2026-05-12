#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    char paragraph[1024];

    // 1. Create socket [cite: 17]
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 2. Connect to server [cite: 20]
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // 3. Input paragraph 
    printf("Enter paragraph (end with Enter): ");
    fgets(paragraph, 1024, stdin);

    // 4. Send data [cite: 23]
    send(sock, paragraph, strlen(paragraph), 0);

    // 5. Receive results [cite: 26]
    read(sock, buffer, 1024);
    printf("Server response: %s\n", buffer); 

    close(sock); 
    return 0;
}