#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int is_faulty()
{
    return rand() % 4 == 0;
}

int main()
{
    srand(time(0));

    int sock;

    struct sockaddr_in server_addr;

    char buffer[100];
    char ack[100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    inet_pton(AF_INET,
              "127.0.0.1",
              &server_addr.sin_addr);

    connect(sock,
            (struct sockaddr *)&server_addr,
            sizeof(server_addr));

    printf("Selective Repeat Client Running...\n");

    while (1)
    {
        read(sock, buffer, sizeof(buffer));

        int seq =
            buffer[strlen(buffer) - 1] - '0';

        printf("Received: %s\n", buffer);

        // Simulate corruption
        if (is_faulty())
        {
            sprintf(ack, "NACK %d", seq);

            printf("Sent: %s\n", ack);
        }
        else
        {
            sprintf(ack, "ACK %d", seq);

            printf("Sent: %s\n", ack);
        }

        write(sock, ack, sizeof(ack));

        if (seq == 9)
            break;
    }

    close(sock);

    return 0;
}