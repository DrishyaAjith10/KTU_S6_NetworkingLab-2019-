#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    socklen_t len;
    char buffer[BUFFER_SIZE];

    // 1. Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    len = sizeof(server_addr);

    printf("UDP Client Ready...\n");

    while (1)
    {
        // Send message
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        sendto(sock,
               buffer,
               strlen(buffer),
               0,
               (struct sockaddr *)&server_addr,
               len);

        // Clear buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Receive reply
        recvfrom(sock,
                 buffer,
                 BUFFER_SIZE,
                 0,
                 (struct sockaddr *)&server_addr,
                 &len);

        printf("Server: %s", buffer);
    }

    close(sock);

    return 0;
}