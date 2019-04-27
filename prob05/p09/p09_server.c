#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER 500
#define ARGS   20

struct arguments
{
    pid_t pid;
    char * argv;
};


int main(void){
    int n, fd;
    int first, second;
    char buffer[BUFFER];
    char * arguments[ARGS] = {NULL};
    char * fifo = "/tmp/fifo.";
    int pid;
    struct arguments args;
    mkfifo("/tmp/fifo.s", 0660);
    while(fd = open("/tmp/fifo.s", O_RDONLY) ){
        while((n = read(fd, &pid, BUFFER)) != 0){
            // tok = strtok(NULL, " ");
            char * argument;
            (n = read(fd, argument, BUFFER) != 0);

            if(fork() > 0){
                // n = read(fd, argument, BUFFER);
                // printf("Meias\n");
                // write(STDOUT_FILENO, buffer, n);
                // arguments[0] = argument;
                printf("Entering cycle!\n");
                // for(int i = 0; i < ARGS; i++){
                //     printf("Meias\n");
                //     argument = args.argv;
                //     // char * tok = strtok(NULL, " ");
                //     // n = read(fd, argument, BUFFER);
                //     // write(STDOUT_FILENO, buffer, n);
                //     printf("First arg: %s\n", argument);
                //     if(argument == NULL){
                //         arguments[i] = NULL;
                //         break;
                //     }
                //     arguments[i] = argument;
                // }
                char fifo_pid[BUFFER];
                sprintf(fifo_pid, "%s%d", fifo, pid);
                printf("Opening %s\n", fifo_pid);
                int fifo_fd = open(fifo_pid, O_WRONLY);
                // dup2(fifo_fd, STDOUT_FILENO);
                printf("Reached here: %s\n", argument);
                execlp(argument, argument);
                printf("Failed to execute exec!\n");
                write(fifo_fd, "STOPPED", strlen("STOPPED"));
                exit(1);
            }
            else
            {
                wait(NULL); 
                printf("Stopped waiting\n");               
            }
        }
        // close(fd);
    }
    printf("Ending!\n");
    return 0;
}