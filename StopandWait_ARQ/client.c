#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
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
    int sock;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    Frame frame;
    Ack ack;

    sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0){
        perror("Socket failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    int seq = 0;

    while(1){
        printf("Enter data: ");
        fgets(frame.data,sizeof(frame),stdin);
        frame.seqno = seq;

        sendto(sock,&frame,sizeof(frame),0,(struct sockaddr *)&server_addr,len);

        recvfrom(sock,&ack,sizeof(ack),0,(struct sockaddr *)&server_addr,&len);
        printf("Ack recieved from %d", ack.ackno);

        seq++;
    }
    close(sock);
    return 0;

}