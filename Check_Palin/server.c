#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "palin.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    struct sockaddr_in server_addr,client_addr;
    socklen_t len = sizeof(client_addr);

    char buffer[BUFFER_SIZE];

    int server_fd;

    server_fd = socket(AF_INET,SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));

    while(1){
        recvfrom(server_fd,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client_addr, &len);
        printf("\nThe Word to be checked: %s ", buffer);

        int pal;
        pal = isPalin(buffer);

        sendto(server_fd,&pal,BUFFER_SIZE,0,(struct sockaddr *)&client_addr, len);
        printf("\nResult Sent");
    }

    close(server_fd);
    return 0;






}