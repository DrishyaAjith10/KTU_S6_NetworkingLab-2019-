#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

typdef struct{
    int seqno;
    char data[100];
}Frame;

typedef struct{
    int ack_no
}Ack;

int main(){
    int server_fd
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;

    Frame frame;
    Ack ack;

    server_fd = socket(AF_INET, SOCK_DGRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr *)&server_addr, sizeof(serveraddr));

    len = sizeof(client_addr);

    while(1){
        recvfrom(server_fd,&frame,sizeof(frame),0,(struct sockaddr *)&client_addr,&len);

        printf("Frame %d, Data %s ",frame.seq_no, frame.data);

        ack.ack_no = fram.seq_no +1;

        sendto(server_fd,&ack,size(ack),0,(struct sockaddr*)&client_addr,len);

        print("%d ack sent", ack.ack_no);


    }
    close(server_fd);
    
    return 0;
}