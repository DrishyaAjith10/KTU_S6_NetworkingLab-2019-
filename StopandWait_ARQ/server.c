#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct{
    int seqno;
    char data[100];

}Frame;

typedef struct{
    int ackno;
}Ack;

int main(){
    int server_fd;

    Frame frame;
    Ack ack;

    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));

    while(1){
        recvfrom(server_fd,&frame,sizeof(frame),0,(struct sockaddr *)&client_addr, &len);
        printf("Client: %s", frame.data);

        ack.ackno = frame.seqno + 1;

        sendto(server_fd,&ack,sizeof(ack),0,(struct sockaddr *)&client_addr,len);
        printf("\n %d Ack sent ", ack.ackno );

    }


    
    close(server_fd);
    return 0;
}