#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, client_fd;

    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    char filename[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    int bytes_received;

    FILE *file;

    // 1. Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("Socket Failed");
        exit(1);
    }

    // 2. Define server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 3. Bind socket
    bind(server_fd,
         (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    // 4. Listen
    listen(server_fd, 5);

    printf("FTP Server Running...\n");

    // 5. Accept connection
    client_fd = accept(server_fd,
                       (struct sockaddr *)&client_addr,
                       &len);

    printf("Client Connected\n");

    // 6. Receive filename
    bytes_received =
        recv(client_fd,
             filename,
             BUFFER_SIZE - 1,
             0);

    // Add null terminator
    filename[bytes_received] = '\0';

    printf("Requested File: %s\n", filename);

    // 7. Open file
    file = fopen(filename, "r");

    // 8. File not found
    if (file == NULL)
    {
        strcpy(buffer, "File Not Found");

        send(client_fd,
             buffer,
             strlen(buffer),
             0);

        printf("File Not Found\n");
    }

    // 9. Send file contents
    else
    {
        while (fgets(buffer,
                     BUFFER_SIZE,
                     file) != NULL)
        {
            send(client_fd,
                 buffer,
                 strlen(buffer),
                 0);

            memset(buffer, 0, BUFFER_SIZE);
        }

        printf("File Sent Successfully\n");

        fclose(file);
    }

    // 10. Close sockets
    close(client_fd);
    close(server_fd);

    return 0;
}