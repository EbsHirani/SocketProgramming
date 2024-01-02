#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 

int main(){
    
    char message[1024] = "Hello from server";
    int socket_fd, client_socket;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    listen(socket_fd, 5);
    client_socket = accept(socket_fd, NULL, NULL);
    send(client_socket, message, sizeof(message), 0);

    close(socket_fd);

    return 0;
}