#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAX_CLIENTS 10

int main() {
    int server_fd, client_socks[MAX_CLIENTS] = {0}, max_sd, sd;
    struct sockaddr_in address;
    fd_set readfds;
    char buffer[1025];

    server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(12345);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address)); 
    listen(server_fd, 5); 
    printf("Part 4: Group & Direct Chat Server started...\n");

    while(1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_sd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socks[i];
            if(sd > 0) FD_SET(sd, &readfds);
            if(sd > max_sd) max_sd = sd;
        }

        select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if (FD_ISSET(server_fd, &readfds)) {
            int new_socket = accept(server_fd, NULL, NULL); 
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if(client_socks[i] == 0) {
                    client_socks[i] = new_socket;
                    printf("New client connected on Socket ID: %d\n", new_socket);
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socks[i];
            if (FD_ISSET(sd, &readfds)) {
                int valread = read(sd, buffer, 1024); 
                if (valread <= 0) {
                    close(sd); 
                    client_socks[i] = 0;
                } else {
                    buffer[valread] = '\0';
                    
                    // DIRECT CHAT LOGIC: Check if message starts with "id:"
                    int target_id = -1;
                    if (sscanf(buffer, "%d:", &target_id) == 1) {
                        char *msg = strchr(buffer, ':') + 1;
                        send(target_id, msg, strlen(msg), 0); // [cite: 25]
                    } else {
                        // GROUP CHAT LOGIC: Relay to all 
                        for (int j = 0; j < MAX_CLIENTS; j++) {
                            if (client_socks[j] != 0 && client_socks[j] != sd) {
                                send(client_socks[j], buffer, strlen(buffer), 0); 
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}