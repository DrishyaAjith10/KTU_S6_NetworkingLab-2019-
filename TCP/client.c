
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sock;
    char buffer[BUFFER_SIZE];

    struct sockaddr_in server_addr;
    sock = socket(AF_INET,SOCK_STREAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1",&server_addr.sin_addr);

    connect(sock,(struct sockaddr *)&server_addr, sizeof(server_addr));

    while(1){
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        if (strncmp(buffer, "EXIT" , 4)== 0 ){
            break;
        }

        send(sock,buffer,strlen(buffer),0);


        memset(buffer,0,BUFFER_SIZE);
        recv(sock,buffer,BUFFER_SIZE,0);
        printf("Server: ");
        printf("%s", buffer);

    }

    close(sock);
    return 0;


    
}