#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "prime.h"

#define BUFFER_SIZE 1024
#define PORT 8080

int main(){
    int sock;
    int number;
    int prime;

    sock = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    connect(sock,(struct sockaddr *)&server_addr, len);

    while(1){

        printf("\nEnter number to be checked: ");
        scanf("%d",&number);

        send(sock,&number,sizeof(number),0);

        
        recv(sock,&prime,sizeof(prime),0);
        if(prime == 0){
            printf("\nThe number is not prime");
        }
        else
        {
            printf("\nThe number is prime");
        }
        
    }

    close(sock);
    return 0;
}