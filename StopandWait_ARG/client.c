#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

typedef struct{
    int seq_no;
    char data[100];
}Frame;

typedef struct{
    int ack_no;
}Ack;

int main(){
    int sock;

    Frame frame;
    Ack ack;

    struct sockaddr_in server_addr;
    socklen_t len;

    sock = socket(AF_INET,SOCK_DRAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_ptons(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    len = sizeof(server_addr);

    int seq =0;

    while(1){
        printf("Enter message: ");
        fgets(frame.data, size(frame.data),stdin);

        frame.seq_no = seq;

        sendto(sock,frame.data,sizeof(frame.data),0,(struct sockaddr *)&server_addr,len);

        printd("Frame is sent");

        recvfrom(sock,&ack,size(ack),0,(struct sockaddr *)&server_addr, &len);

        printf("Ack no: ",ack.ack_no);

        seq++;


    }

    close(sock);
    




    return 0;
}