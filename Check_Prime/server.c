#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "prime.h"

#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
    int server_fd,client_fd;
    int number;
    int result;


    server_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));

    listen(server_fd,5);
    printf("TCP Server is listening\n");

    client_fd = accept(server_fd,(struct sockaddr *)&client_addr, &len);

    while(1){
        recv(client_fd,&number,sizeof(number),0);
        printf("\n The number is %d", number);

        result = isPrime(number);

        send(client_fd,&result,sizeof(result),0);
        printf("\nResult is Sent");
        
    }
    close(client_fd);
    close(server_fd);
}