#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "string.h"
#define PORT 9004
#define MAXLINE 30
int main()
{
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    char serverResponse[MAXLINE];
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);
    connect(socket_descriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    recv(socket_descriptor, serverResponse, MAXLINE - 1, 0);
    printf("\nTIME FROM SERVER %s\n", serverResponse);
    return 0;
}