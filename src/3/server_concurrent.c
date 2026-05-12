#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

void process_request(int clnt_sock) {
    char buffer[1024] = {0};
    read(clnt_sock, buffer, 1024);
    
    int chars = strlen(buffer);
    int words = 0, sentences = 0;
    
    for(int i = 0; buffer[i] != '\0'; i++) {
        if(buffer[i] == ' ' || buffer[i] == '\n') words++;
        if(buffer[i] == '.') sentences++;
    }
    if(chars > 0 && words == 0) words = 1;

    char response[100];
    sprintf(response, "Chars: %d, Words: %d, Sentences: %d", chars, words, sentences);
    send(clnt_sock, response, strlen(response), 0);
    
    close(clnt_sock); // Child closes the specific client socket
    exit(0); // Child process terminates after serving
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(12345);
    
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);
    
    // Prevent zombie processes
    signal(SIGCHLD, SIG_IGN);

    printf("Concurrent Server listening on port 12345...\n");

    while(1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        // Create a child process to handle the client
        pid_t pid = fork();
        
        if (pid == 0) { // Child Process
            close(server_fd); // Child doesn't need the listener
            process_request(new_socket);
        } else { // Parent Process
            close(new_socket); // Parent doesn't need this specific client socket
        }
    }

    close(server_fd);
    return 0;
}