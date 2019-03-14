#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

bool increase = false;

void usr_handler(int signo){
    if(signo == SIGUSR1){
        printf("Increasing variable...\n");
        increase = true;
    }
    else if(signo = SIGUSR2)
    {
        printf("Decreasing variable...\n");
        increase = false;
    }
    
}

int main(){
    int v = 0;
    struct sigaction action;
    action.sa_handler = usr_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if(sigaction(SIGUSR1, &action, NULL) < 0){
        fprintf(stderr, "Unable to install handler\n");
        exit(1);
    }

    if(sigaction(SIGUSR2, &action, NULL) < 0){
        fprintf(stderr, "Unable to install handler\n");
        exit(1);
    }
    while(1){
        printf("Variable: %d\n", v);
        if(increase)
            v++;
        else
            v--;
        sleep(1);
    }
    exit(1);
}