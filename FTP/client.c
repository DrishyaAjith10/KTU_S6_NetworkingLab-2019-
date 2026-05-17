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
    char filename[BUFFER_SIZE];

    sock = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
        

    connect(sock,(struct sockaddr * )&server_addr, sizeof(server_addr));

    printf("Enter file name : ");
    scanf("%s", filename);

    send(sock,filename,strlen(filename) , 0);

    
    while(recv(sock,buffer,BUFFER_SIZE,0)>0){
        printf("%s", buffer);

        memset(buffer,0,BUFFER_SIZE);
    }

    close(sock);

    return 0;



}
