#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int pid, nbytes = 0;
    int pipefd[2];
    char buff[1024];
    
    if(pipe(pipefd) < 0)
    {
        printf("pipe error");
        exit(1);
    }

    pid = fork();

    // Child process
    if(pid == 0)
    {
        // Close unused read
        close(pipefd[0]);
        // Copy pipefd[1] to stdout
        dup2(pipefd[1], 1);
        execl("/bin/ls", "/bin/ls", NULL);
    }

    // Close unused write
    close(pipefd[1]);
	
	// Copy output
    while((nbytes = read(pipefd[0], buff, sizeof(buff))) > 0)
    {
        write(1, buff, nbytes);
    }
    
    close(pipefd[0]);

    return 0;
}
