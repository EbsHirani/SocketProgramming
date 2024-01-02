#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 

int main() {
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    char response[1024];

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        printf("connect failed\n");
        exit(1);
    }

    recv(socket_fd, response, sizeof(response), 0);

    printf("response from server: %s\n", response);
    close(socket_fd);
    return 0;
}