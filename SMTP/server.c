#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(){
    int server_fd,client_fd;

    struct sockaddr_in server_add, client_addr;
    socklen_t len = sizeof(client_addr);

    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM , 0);

    server_addr.s_family = AF_INET;
    server_addr.s_port = htons(PORT);
    server_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd,5);

    printf("SMTP running successfully\n");

    send(client_fd,"220 SMTP Server is ready ",25,0);


    while(1){
        memset(buffer,0,BUFFER_SIZE);

        recv(client_fd,buffer,BUFFER_SIZE,0);

        printf("Client: %s", buffer);

        if (strncmp(buffer,"HELO",4,0) == 0){
            send(client_fd,"250 Hello\r\n",11,0);
        }

        else if(strncmp(buffer,"MAIL FROM",9,0)==0){
            send(client_fd, "250 OK\r\n",8,0);
        }

        else if (strncmp(buffer,"RCPT TO",7,0)== 0){
            send(client_fd,"250 OK\r\n",8,0);
        }
        else if (strncmp(buffer,"DATA",4,0)== 0){
            send(client_fd,"354 Enter Mail Body\r\n",21,0);
        }
        else if(strcmp(buffer,".\r\n")== 0){
            send(client_fd,"250 OK\r\n",8,0);
        }
        else if(strncmp(buffer,"QUIT",4,0)==0){
            send(client_fd,"221 Bye\r\n",7,0);
            break;
        }
        else{
            printf("Body of message : %s ",buffer);
        }

    }
    close(client_fd);
    close(server_fd);

    return 0;

}