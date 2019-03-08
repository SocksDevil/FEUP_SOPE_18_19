#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <unistd.h>


int main(void){
    int pid, status;
    pid = fork();

    if(pid > 0){
        wait(&status);
        if(status == 0)
            printf("friends!\n");
    }
    else
    {
        pid = fork();
        if(pid > 0){
            wait(&status);
            if(status == 0)
            {
                printf("my ");
                exit(0);
            }
            exit(1);

        }
        else
        {
            printf("Hello ");
            exit(0);
        }
        
    }
    return 0;    
}