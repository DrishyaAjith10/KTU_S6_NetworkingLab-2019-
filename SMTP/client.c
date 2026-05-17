#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int sock;
    sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr;

    char buffer[BUFFER_SIZE];

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    ptons_inet(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    connect(sock,(stuct sockaddr*)&server_addr, sizeof(server_addr));

    recv(sock,buffer,BUFFER_SIZE,0);
    printf("Server: %s ",buffer);

    strcpy(buffer, "HELO server\r\n");
    send(sock,buffer,strlen(buffer),0);
    recv(sock,buffer,BUFFER_SIZE,0);
    printf("Server: %s ",buffer);

    strcpy(buffer,"MAIL FROM : drishyaajith10@gmail.com\r\n");
    send(sock,buffer,strlen(buffer),0);
    recv(sock,buffer,BUFFER_SIZE,0);
    printf("Server: %s ",buffer);

    strcpy(buffer,"RCPT TO: indurv.in@gmail.com\r\n");
    send(sock,buffer,strlen(buffer),0);
    recv(sock,buffer,BUFFER_SIZE,0);
    printf("Server: %s ",buffer);

    strcpy(buffer,"DATA\r\n");
    send(sock,buffer,strlen(buffer),0);
    recv(sock,buffer,BUFFER_SIZE,0);
    printf("Server: %s ",buffer);

    printf("Enter the body of the MAIL: ");
    fgets(buffer,BUFFER_SIZE,stdin);
    send(sock,buffer,strlen(buffer),0);


    strcpy(buffer,".\r\n");
    send(sock,buffer,strlen(buffer),0);
    recv(sock,buffer,BUFFER_SIZE,0);
    printf("Server: %s ",buffer);

    strcpy(buffer,"QUIT\r\n");
    send(sock,buffer,strlen(buffer),0);
    recv(sock,buffer,BUFFER_SIZE,0);
    printf("Server: %s ",buffer);

    close(sock);

    return 0;
}
