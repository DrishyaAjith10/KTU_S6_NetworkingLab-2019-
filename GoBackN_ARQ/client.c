#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
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

    printf("Go-Back-N Client Running...\n");

    int expected = 0;
    int ack_lost = 0;

    while (expected < 10)
    {
        read(sock, buffer, sizeof(buffer));

        int seq =
            buffer[strlen(buffer) - 1] - '0';

        // Out-of-order frame discard
        if (seq != expected)
        {
            printf("Discarded Frame %d\n", seq);

            continue;
        }

        // Simulate ACK loss
        if (seq == 5 && ack_lost == 0)
        {
            printf("Simulating ACK Loss for Frame %d\n",
                   seq);

            ack_lost = 1;

            continue;
        }

        printf("Received: %s\n", buffer);

        sprintf(ack, "ACK %d", seq);

        write(sock, ack, sizeof(ack));

        printf("Sent: %s\n", ack);

        expected++;
    }

    close(sock);

    return 0;
}