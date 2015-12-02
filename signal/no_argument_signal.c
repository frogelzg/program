#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum)
{
    printf("Handle signal!\n");
    switch(signum)
    {
    case SIGHUP:
        printf("Get a signal of SIGHUP!\n");
        break;
    case SIGINT:
        printf("Get a signal of SIGINT!\n");
        break;
    case SIGQUIT:
        printf("Get a signal of SIGQUIT!\n");
        break;
    default:
        printf("Get nothing!\n");
    }
    /* If handle completely, continue to run background. */
//    printf("pid is %d.\n", getpid());
//    daemon(1, 1);
}

int main()
{
    printf("This is a simple sample of signal!\n");
    printf("Running background!\n");
    printf("pid is %d.\n", getpid());
    /* Running background */
    daemon(1, 1);

    /* Register signals */
    signal(SIGHUP, handler);
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);

    while(1);
    
    wait(NULL);
    return 0;
}
