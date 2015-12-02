#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT    12345

int bios_open_socket(void)
{
    int fd;
    struct sockaddr_in addr;
    char    *address;

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

    /* print the address of INADDR_ANY */
    address = inet_ntoa(addr.sin_addr);
    printf("IP address of INADDR_ANY is %s.\n", address);

    return fd;
}

int main()
{
    int fd;

    fd = bios_open_socket();    
    printf("Fd is %d.\n", fd);

    return 0;
}
