#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080
#define WINDOW_SIZE 3
#define TOTAL_FRAMES 10

int main(){

    int client_fd,server_fd;
    struct sockaddr_in server_addr,client_addr;
    socklen_t len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM,0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    char buffer[250];
    char ack[100];

    bind(server_fd,(struct sockaddr *)&server_addr , sizeof(server_addr));

    listen(server_fd,5);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &len);

    int base =0;
    int next_frame = 0;
    while(base < TOTAL_FRAMES){
        while(nextframe < base + WINDOW_SIZE && nextframe < TOTAL_FRAMES){
            sprintf(buffer, "Frame %d",next_frame);
            write(client_fd,buffer,sizeof(buffer));
            printf("Sent: ",buffer);
            next_frame ++;

        }
        fd_set readfds;
        struct timeval tv;

        FD_ZERO(&readfds);
        FD_SET(client_fd,&readfds);

        tv.tv_sec = 2;
        tv.tv_usec =0;

        int rv = select(client_fd + 1,&readfds,NULL,NULL,&tv);
        if (rv == 0)
        {
            printf("Timeout! Retransmitting from Frame %d\n",
                   base);

            next_frame = base;
        }
        else
        {
            read(client_fd, ack, sizeof(ack));

            printf("Received: %s\n", ack);

            base++;
        }
    }
    close(client_fd);
    close(server_fd);


    return 0;
}