#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void new_op(int,siginfo_t*,void*);
void Usage(void);
void matchsig(char *argv, int *sig);

int main(int argc,char**argv)
{
        struct sigaction act;  
        int 	sig;
       
        if(argc != 2)
        {
            Usage();
            return 0;
        }

        matchsig(argv[1], &sig);

        sigemptyset(&act.sa_mask);
        act.sa_flags=SA_SIGINFO;
        act.sa_sigaction=new_op;

        if(sigaction(sig,&act,NULL) < 0)
        {
 	       printf("install sigal error\n");
        }       

        while(1)
        {
                sleep(2);
                printf("wait for the signal\n");
        }
}

 

void new_op(int signum,siginfo_t *info,void *myact)
{
        printf("receive signal %d.\n", signum);

        sleep(5);
}

void Usage()
{
    printf("Usage: sigaction signum\n");
}

void matchsig(char *argv, int *sig)
{
    if(!strcmp(argv, "SIGINT"))
    {
        *sig = SIGINT;
        return;
    }

    if(!strcmp(argv, "SIGQUIT"))
    {
        *sig = SIGQUIT;
        return;
    }

    if(!strcmp(argv, "SIGHUP"))
    {
        *sig = SIGHUP;
        return;
    }

    printf("Get error signal!\n");
    *sig = -1;
}
