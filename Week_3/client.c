#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define bzero(b, len) (memset((b), '\0', (len)), (void)0)
#define SA struct sockaddr
const int max = 80;
const int port = 9000;
void func(int sockfd)
{
    char buff[max];
    int n = 0;
    for (;;)
    {
        bzero(buff, sizeof(buff));
        printf("\nEnter the message : ");
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        printf("From server : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0)
        {
            printf("\nClient exit.!");
            break;
        }
    }
}
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket creation failed...");
        exit(0);
    }
    else
    {
        printf("\nSocket created successfully...");
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port);
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("\nSocket connection failed.!");
        exit(0);
    }
    else
    {
        printf("\nSocket connection successful...");
    }
    func(sockfd);
    close(sockfd);
    return 0;
}