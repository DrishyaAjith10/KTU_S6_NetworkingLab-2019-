#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_fd,client_fd;
    char buffer[BUFFER_SIZE];

    struct sockaddr_in server_addr,client_addr;
    socklen_t len;

    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if (server_fd < 0){
        perror("Socket failed");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    len = sizeof(client_addr);

    bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));

    listen(server_fd,5);
    printf("Listening to client");

    client_fd = accept(server_fd,(struct sockaddr *)&client_addr, &len);

    while(1){
        memset(buffer,0, BUFFER_SIZE);

        recv(client_fd,buffer,BUFFER_SIZE,0);
        if (strncmp(buffer, "EXIT", 4) == 0)
        {
            break;
        }
        printf("Client: %s", buffer);

        printf("Sever: ");
        fgets(buffer, BUFFER_SIZE , stdin);
        send(client_fd,buffer,strlen(buffer),0);

    }

    close(client_fd);
    close(server_fd);

    return 0;




}


