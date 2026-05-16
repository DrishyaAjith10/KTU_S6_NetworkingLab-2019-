#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;
    char buffer[BUFFER_SIZE];

    // 1. Create UDP socket
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 3. Bind socket
    bind(server_fd,
         (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    len = sizeof(client_addr);

    printf("UDP Server listening on port %d...\n", PORT);

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message
        recvfrom(server_fd,
                 buffer,
                 BUFFER_SIZE,
                 0,
                 (struct sockaddr *)&client_addr,
                 &len);

        printf("Client: %s", buffer);

        // Send reply
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        sendto(server_fd,
               buffer,
               strlen(buffer),
               0,
               (struct sockaddr *)&client_addr,
               len);
    }

    close(server_fd);

    return 0;
}