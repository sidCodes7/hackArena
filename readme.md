# Socket Programming in C (Linux)
## 1 Server + 2 Clients Communication

---

# server.c

```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int server_fd, client1, client2;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind socket
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen for clients
    listen(server_fd, 2);

    printf("Waiting for Client 1...\n");

    // Accept Client 1
    client1 = accept(server_fd, NULL, NULL);

    // Receive message from Client 1
    recv(client1, buffer, sizeof(buffer), 0);

    printf("Client1 says: %s\n", buffer);

    printf("Waiting for Client 2...\n");

    // Accept Client 2
    client2 = accept(server_fd, NULL, NULL);

    // Send Client1 message to Client2
    send(client2, buffer, strlen(buffer), 0);

    // Receive reply from Client2
    recv(client2, buffer, sizeof(buffer), 0);

    printf("Client2 says: %s\n", buffer);

    // Send Client2 reply back to Client1
    send(client1, buffer, strlen(buffer), 0);

    // Close sockets
    close(client1);
    close(client2);
    close(server_fd);

    return 0;
}
client1.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // Connect to server
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Send message to server
    send(sock, "Hi from Client1", 15, 0);

    // Receive reply from Client2
    recv(sock, buffer, sizeof(buffer), 0);

    printf("Client2 says: %s\n", buffer);

    // Close socket
    close(sock);

    return 0;
}
client2.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    // Connect to server
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Receive Client1 message
    recv(sock, buffer, sizeof(buffer), 0);

    printf("Client1 says: %s\n", buffer);

    // Send reply back
    send(sock, "Hello from Client2", 18, 0);

    // Close socket
    close(sock);

    return 0;
}
Compile Commands
gcc server.c -o server

gcc client1.c -o client1

gcc client2.c -o client2
Run Commands
Terminal 1
./server
Terminal 2
./client1
Terminal 3
./client2






CCN Lab ESE Prep:

#1

Ifconfig ⇒ view ip, mac 
ping ⇒ internet working, server online, latency test, detect packet loss
Nslookup ⇒ ip of domain using DNS servers
Traceroute ⇒ data packet route from source to dest
Netstat -tuln ⇒ Active TCP/UDP ports on system

#2

Waterfall view ⇒ loading sequence + resource duration

Each resource (click on the Name) has:

Network
Headers (Request + Response)
Timing (TTFB → Time to First Byte) ⇒Server Response Time
Throttling

Performance
Record & Reload 

#3

Steps for TCP communication:

Server runs first and waits
socket() → Endpoint for connection b/w 2 processes over a network
bind()
listen()
accept()

Client runs
socket()
connect()

Client Sends Data
send()

Server Receives Data
recv()

Server Processes & Sends
Result = a + b
send()

Client Receives & closes
recv()
close()

Server detect disconnection & closes
close()

#4

HTTP ⇒ Stateless Protocol (Independent Request, No history maintained)

HTTP Message:
Request Line
Response/Status Line
Header Fields
Message Body

HTTP Methods:
GET
HEAD
POST

HTTP Status Codes:
200 OK
304 Not Modified ⇒ Cached Resource Still Valid
401 Unauthorized
301 Moved Permanently

#6

Commands:
sudo apt-get install nmap 
nmap -sn 10.10.64.69  ⇒ Identify Active Hosts in network range (ifconfig) + MAC
nmap --top-ports 5 10.10.64.69 (Instead of sn scanning all 65535 ports)
nmap target_ip ⇒ common open ports
nmap -p port_no -sV target_ip ⇒ Detect Presence, Detect Version
HTTP 80
HTTPS 443
FTP 21
SSH 22
DNS 53
TELNET 23
RDP 3389
nmap -O target_ip ⇒ Detect OS
sudo nmap -sS target_ip ⇒ Sudo gives admin permissions, 
sudo nmap -sV target_ip ⇒ Software Version
sudo nmap --script default target_ip ⇒ Default nmap scripts

#7

Commands:
sudo scapy
packet = IP(dst="8.8.8.8")/ICMP()  ⇒ Ping
reply = sr1(packet) 
reply.show() 

Other Packet Types:
packet = IP(dst="8.8.8.8")/UDP(dport=53)/"Hello" 
packet = IP(dst="8.8.8.8")/UDP(dport=53)/DNS(rd=1,qd=DNSQR(qname="google.com"))
packet = IP(dst="example.com")/TCP(dport=80, flags="S") ⇒ SYN Packet

#8

Commands:
sudo iptables -L -v ⇒ View Rules, View Packets
sudo iptables -F ⇒ Delete Rules
sudo iptables -A INPUT -p icmp -j DROP ⇒ Block ICMP / Ping Commands
sudo iptables -F ⇒ Allow ICMP again
sudo iptables -L ⇒ Test Connectivity
sudo iptables -N mychain ⇒ Create Custom Chain, Delete with -X
sudo iptables -L OUTPUT -v

#9

Network 1 ⇒ PC → Switch → Router
Network 2 ⇒ Router → PC
