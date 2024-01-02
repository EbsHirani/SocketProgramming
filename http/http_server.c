#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <string.h>

int main(){

    FILE* html_data;
    html_data = fopen("index.html", "r");

    char response_data[1024];
    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    
    fgets(response_data, 1024, html_data);
    strcat(http_header, response_data);

    int socket_fd, client_socket;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8001);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    listen(socket_fd, 5);
    while(1){
        client_socket = accept(socket_fd, NULL, NULL);
        printf("Client connected\n");
        printf("%s\n", http_header);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }

    close(socket_fd);

    return 0;
}