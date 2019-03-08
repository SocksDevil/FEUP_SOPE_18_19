#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    pid_t pid;
    if (argc != 2) {
        printf("usage: %s dirname\n",argv[0]);
        exit(1);
    }
    pid=fork();
    if (pid > 0)
        printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
    else if (pid == 0){
        char * arguments[4];
        char * cmd = "/bin/ls";
        char * newEnv[1];
        newEnv[0] = NULL;
        arguments[0] = "/bin/ls";
        arguments[1] = "-laR";
        arguments[2] = argv[1];
        arguments[3] = NULL;
        execve(cmd, arguments, newEnv);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}

