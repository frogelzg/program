#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0
#define BUFF    1024
#define PORT    1234
#define IP      "192.168.1.2"

int main()
{
    int fd;
    struct sockaddr_in addr;
    socklen_t length = sizeof(addr);
    ssize_t size;
    char buff[BUFF] = {0};

    /* Create a socket to communicate with server */
    if((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("Socket error!");
        exit(1);
    }
    else
    {
        printf("Cteate a socket success! fd: %d\n", fd);
    }

    /* Configure the server address */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_port = htons(PORT);

    /* Connect to the server socket */
    if(connect(fd, (struct sockaddr*)&addr, length) < 0)
    {
        perror("Connect error!");
        exit(1);
    }
    else
    {
        printf("Connect success!\n");
    }

    /* buff */
    printf("Input send data:");
    fflush(stdin);
    if(fgets(buff, BUFF, stdin) < 0)
    {
        perror("fegts() fail!");
        exit(1);
    }

    /* Write/send data to server socket */
    size = write(fd, buff, strlen(buff));

    if(size < 0)
    {
        perror("write() fail!");
        exit(1);
    }
    else
    {
        printf("Write success!\n");
        printf("Send data： %s", buff);
    }
   
    /* Read/receive from server socket */
    size = read(fd, buff, BUFF);
    if(size < 0)
    {
        perror("read() fail!");
        exit(1);
    }
    else
    {
        printf("Receive a reponse: %s", buff);
    }

    /* Remember close all fd */
    close(fd);

    return 0;
}
