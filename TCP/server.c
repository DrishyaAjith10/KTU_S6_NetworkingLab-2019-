#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>.
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080
#define buffer_Size 1024

int main(){
    int server_fd, client_fd;
    struct socketaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[buffer_Size];

    server_fd = socket(AF_INET,SOCK_STREM, 0);
    if(server_fd < 0){
        perror("Socket failed")
        exit(1)
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct socketaddr*)&server_addr,sizeof(server_addr));

    listen(server_fd,1);

    client_fd = accept(server_fd,(struct socketaddr*)&client_addr, &addr_len);

    while(1){
        memset(buffer,0,buffer_Size);

        recv(client_fd,buffer,buffer_Size,0);
        printf("Client: ", buffer);

        printf("Server:")
        fgets(buffer,bufferSize,stdin);
        send(client_fd,buffer,strlen(buffer),0);
    }

    close(client_fd);
    close(server_fd);
    return 0;

}
