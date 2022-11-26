#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#define SA struct sock
#define bzero(b, len) (memset((b), '\0', (len)), (void)0)
const int max = 80;
const int port = 9000;
void func(int connfd)
{
    char buff[max];
    int n = 0;
    for (;;)
    {
        bzero(buff, max);
        read(connfd, buff, sizeof(buff));
        printf("\nFrom client : %s\t To client : ", buff);
        bzero(buff, max);
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(connfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("\nSocket bind failed.!");
            break;
        }
    }
}
int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket creation failed.!");
        exit(0);
    }
    else
    {
        printf("\nSocket created successfully...");
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("\nSocket bind failed.!");
        exit(0);
    }
    else
    {
        printf("\nSocket bind successfully.!");
    }
    if ((listen(sockfd, 5)) != 0)
    {
        printf("\nSocket listen failed.!");
        exit(0);
    }
    else
    {
        printf("\nSocket listening....");
    }
    len = sizeof(cli);
    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        printf("\nSocket accept failed.!");
        exit(0);
    }
    else
    {
        printf("\nSocket accepted the client...");
    }
    func(connfd);
    close(sockfd);
    return 0;
}