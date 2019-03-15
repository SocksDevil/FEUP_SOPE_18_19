#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_ARGUMENTS 50

int main(int argc, char ** argv){
    pid_t children[MAX_ARGUMENTS];
    for(int i = 0; i < MAX_ARGUMENTS; i++){
        if(argv[i + 1] == NULL)
            break;
        pid_t pid = fork();
        if(pid > 0){
            children[i] = pid;
            setpgid(pid, children[0]);
        }
        else
        {
            execlp(argv[i + 1], argv[i + 1], NULL);
            printf("Failed to execute!\n");
            exit(1);
        }
    }

    for(int i = 0; i < MAX_ARGUMENTS; i++){
        if(argv[i + 1] == NULL)
            break;
        int status;
        wait(&status);
        if(status != 0)
        {
            printf("Process failed to execute correctly! Killing all children\n");
            kill(-children[0], SIGKILL);
        }
    }
    return 0;

}