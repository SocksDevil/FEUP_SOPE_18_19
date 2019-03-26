#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER 500
#define ARGS   20

int main(void){
    int n, fd;
    int first, second;
    char buffer[BUFFER];
    char * arguments[ARGS] = {NULL};
    char * fifo = "/tmp/fifo.";
    int pid;
    mkfifo("/tmp/fifo.s", 0660);
    while(fd = open("/tmp/fifo.s", O_RDONLY) ){
        while((n = read(fd, buffer, BUFFER)) != 0){
            char * tok = strtok(buffer, " ");
            pid = atoi(tok);
            // tok = strtok(NULL, " ");
            char * argv[] = strtok(NULL, " ");
            if(fork() == 0){
                char * argument;
                // n = read(fd, argument, BUFFER);
                // printf("Meias\n");
                // write(STDOUT_FILENO, buffer, n);
                // arguments[0] = argument;
                for(int i = 0; i < ARGS; i++){
                    // char * tok = strtok(NULL, " ");
                    // n = read(fd, argument, BUFFER);
                    // write(STDOUT_FILENO, buffer, n);
                    // if(argument == NULL){
                    //     arguments[i] = NULL;
                    //     arguments[i - 1][strlen(arguments[i - 1]) - 1] = '\0';
                    //     break;
                    // }
                    arguments[i] = argument;
                }
                char fifo_pid[BUFFER];
                sprintf(fifo_pid, "%s%d", fifo, pid);
                printf("Opening %s\n", fifo_pid);
                int fifo_fd = open(fifo_pid, O_WRONLY);
                dup2(fifo_fd, STDOUT_FILENO);
                execvp(arguments[0], arguments);
                printf("Failed to execute exec!\n");
                exit(1);
            }
            else
            {
                printf("PID %d initializing work...\n", pid);
            }
        }
        close(fd);
    }
    return 0;
}