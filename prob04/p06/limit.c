#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void child_handler(int signo){
    wait(NULL);
    printf("Child ended succesfully");
    exit(0);
}

int main(int argc, char ** argv){
    if(argc != 4){
        printf("Usage: limit t prog msg\n");
        exit(1);
    }
    pid_t pid;
    pid = fork();
    if(pid > 0){
        int alarm_time = atoi(argv[1]);
        struct sigaction action;
        action.sa_handler = child_handler;
        sigemptyset(&action.sa_mask);        
        action.sa_flags = 0;
        sigaction(SIGCHLD, &action, NULL);
        sleep(alarm_time);
        action.sa_handler = SIG_DFL;
        sigaction(SIGCHLD, &action, NULL);
        kill(pid, SIGKILL);
        wait(NULL);
        printf("Child failed to end in time");
        exit(1);
    }
    else
    {
        execl(argv[2], argv[2], argv[3]);
        printf("Failed to execute %s!\n", argv[2]);
        exit(1);
    }
    
}