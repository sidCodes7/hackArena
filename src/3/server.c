#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // 1. Create socket [cite: 12]
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. Bind to port 12345 [cite: 13]
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(12345);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // 3. Listen [cite: 16]
    listen(server_fd, 3);
    printf("Server listening on port 12345...\n");

    // 4. Accept connection [cite: 18]
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // 5. Receive paragraph [cite: 22]
    read(new_socket, buffer, 1024);
    
    // Process string 
    int chars = 0, words = 0, sentences = 0;
    chars = strlen(buffer);
    for(int i = 0; buffer[i] != '\0'; i++) {
        if(buffer[i] == ' ' || buffer[i] == '\n') words++;
        if(buffer[i] == '.') sentences++;
    }
    if(chars > 0 && words == 0) words = 1; // Handle single word

    // 6. Send results back [cite: 23]
    char response[100];
    sprintf(response, "Chars: %d, Words: %d, Sentences: %d", chars, words, sentences);
    send(new_socket, response, strlen(response), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}