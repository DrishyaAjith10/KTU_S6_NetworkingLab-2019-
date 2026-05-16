#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define WINDOW_SIZE 3
#define TOTAL_FRAMES 10

int main()
{
    int server_fd, client_fd;

    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    char buffer[100];
    char ack[100];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd,
         (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    listen(server_fd, 5);

    printf("Selective Repeat Server Running...\n");

    client_fd = accept(server_fd,
                       (struct sockaddr *)&client_addr,
                       &len);

    int frame = 0;

    while (frame < TOTAL_FRAMES)
    {
        sprintf(buffer, "Frame %d", frame);

        write(client_fd, buffer, sizeof(buffer));

        printf("Sent: %s\n", buffer);

        read(client_fd, ack, sizeof(ack));

        printf("Received: %s\n", ack);

        // NACK received
        if (strncmp(ack, "NACK", 4) == 0)
        {
            printf("Resending Frame %d\n", frame);
        }
        else
        {
            frame++;
        }
    }

    close(client_fd);
    close(server_fd);

    return 0;
}