#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    int status;
    pid=fork();
    if (pid > 0)
    {
        wait(&status);
        printf("My child returned with exit code %d", status);
    }
    else if (pid == 0){
        if(argc > 2)
        {
            int fd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL);
            dup2(fd, STDOUT_FILENO);            
        }
        execlp("ls", "ls", "-laR", argv[1], NULL);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}

