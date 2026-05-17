

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sock;
    char buffer[BUFFER_SIZE];
    
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    sock = socket(AF_INET,SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    while(1){
        memset(buffer,0, BUFFER_SIZE);

        printf("Client: ");
        fgets(buffer,BUFFER_SIZE,stdin);
        if(strncmp(buffer, "exit",4)== 0){
            break;
        }
        sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)&server_addr,len);

        memset(buffer,0, BUFFER_SIZE);
        printf("Server: ");
        recvfrom(sock,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_addr,&len);
        printf("%s", buffer);


    }

    close(sock);
    return 0;



}