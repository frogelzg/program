#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <net/if.h>
#include <arpa/inet.h>

#define BACKLOG     5
#define PORT        1234
#define TRUE        1
#define FALSE       0
#define BUFF        1024
#define CLIENTLEN   10

struct client_addr
{
    char    ip_addr[15];
    unsigned short port;
}__attribute((packed, aligned(4)))__;

typedef struct client_addr client_addr;

int bios_open_socket(void);
int add_client_addr(client_addr *client, char *address, unsigned short port);
int show_client_addr(client_addr *client);

int main()
{
    int         fd,ss;
    int         listen_num;
    struct sockaddr_in addr;
    socklen_t   length = sizeof(addr);
    ssize_t     size;
    char        buff[BUFF] = {0};
    /* a config struct */
    struct      ifreq ifr;
    char        *address;
    unsigned short  port;
    client_addr client[CLIENTLEN];

    memset(client, 0, sizeof(client));

    /* Create a socket */
    fd = bios_open_socket();
    if(fd < 0)
    {
        printf("%d error：bios_open_socket！\n", __LINE__);
        exit(1);
    }
    else
    {
        printf("bios_open_socket success! fd: %d\n", fd);
    }
    
    daemon(1, 1);

    /* Listen the fd */
    listen_num = listen(fd, BACKLOG);
    if(listen < 0)
    {
        printf("%d error：listen！\n", __LINE__);
        exit(1);
    }
    else
    {
        printf("Listen success! listen_num: %d\n", listen_num);
        printf("(If success, return 0, else the result returned less than 0)\n");
    }
    
    /* Recursive accept the request */
    while(TRUE)
    {
        /* A new socket to accept the client request */
        ss = accept(fd, (struct sockaddr*)&addr, &length);
        if(ss < 0)
        {
            printf("%d error: accept!\n", __LINE__);
            exit(1);
        }
        else
        {
            printf("Accept success！ss: %d\n", ss);
            /* Get the IP address of client socket */
//            if(ioctl(ss, SIOCGIFADDR, &ifr) == -1)
//            {
//                perror("Line: %d ioctl() erroe!", __LINE__);
//                exit(1);
//            }
//            addr = *((struct sockaddr_in *)&(ifr.ifr_addr));
            address = inet_ntoa(addr.sin_addr);
            port    = ntohs(addr.sin_port);
            printf("Client address：%s.\n", address);
            printf("Client port: %d.\n", port);
            add_client_addr(client, address, port);
        }
        /* receive the data from client */
        size = read(ss, buff, BUFF);
        if(size < 0)
        {
            printf("%d error: read!\n", __LINE__);
            exit(1);
        }
        else
        {
            printf("Read success! buff: %s", buff);
        }

        /* Response */
        printf("Need reponse(default not response):");
        if(fgets(buff, BUFF, stdin) < 0)
        {
            perror("fgets() fail!");
            exit(1);
        }
        size = strlen(buff);
        printf("strlen: %ld\n", size);
        if(size > 1)
        {
            size = write(ss, buff, sizeof(buff));
            printf("Response: %s", buff);
        }
    }
    
    /* Remember that you must close all fd which have opend */
    close(fd);
    close(ss);

    return 0;
}

int add_client_addr(client_addr *client, char *address, unsigned short port)
{
    int i;

    for(i = 0; i < CLIENTLEN; i++)
    {
        if(!strcmp(client[i].ip_addr, address) && (client[i].port == port))
        {
            printf("Have same socket in addr array!\n");
            return 0;
        }
    }

    if(i >= CLIENTLEN)
    {
        printf("Over array!\n");
        return -1;
    }

    return 0;
}

int bios_open_socket(void)
{
    int fd;

    struct sockaddr_in addr;
    /* Create a socket */
    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fd < 0)
        return -1;
    
    /* configure the server address */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    /* Bind the address on the fd */
    if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind() error!");
        return -1;
    }

    return fd;
}

int show_client_addr(client_addr *client)
{
    int i;

    for(i = 0; i < CLIENTLEN; i++)
    {
        printf("%d.\n", i);
        printf("ip address: %s.\n", client[i].ip_addr);
        printf("port: %d.\n", client[i].port);
    }

    return 0;
}
