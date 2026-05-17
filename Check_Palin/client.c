#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "palin.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    int buffer[BUFFER_SIZE];

    int sock;

    sock = socket(AF_INET,SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    while(1){

        printf("\nEnter Word to be checked: ");
        fgets(buffer,BUFFER_SIZE,stdin);

        sendto(sock,buffer,BUFFER_SIZE,0,(struct sockaddr *)&server_addr, len);

        int pal;

        recvfrom(sock,&pal,BUFFER_SIZE,0,(struct sockaddr *)&server_addr, &len);
        if(pal==0){
            printf("\nThe Word is not a Palindrome ");
        }
        else{
            printf("\nThe Word is a Palindrome ");
        }
    }

    close(sock);
    return 0;






}