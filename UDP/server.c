
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_fd;
    struct sockaddr_in server_addr,client_addr;
    socklen_t len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];


    server_fd = socket(AF_INET,SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("UDP Server is listening");

    while(1){
        memset(buffer,0,BUFFER_SIZE);
        recvfrom(server_fd,buffer,BUFFER_SIZE,0,(struct sockaddr *)&client_addr,&len);
        if(strncmp(buffer, "exit",4)== 0){
            break;
        }

        printf("Client: %s",buffer);

        printf("Server: ");
        memset(buffer,0,BUFFER_SIZE);
        fgets(buffer,BUFFER_SIZE,stdin);
        sendto(server_fd,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,len);
    }
    close(server_fd);
    return 0;
}