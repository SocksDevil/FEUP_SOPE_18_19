#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER 500

int main(void){
    int n, fd;
    int first, second;
    char buffer[BUFFER];
    mkfifo("/tmp/fifo_serv", 0660);
    while(fd = open("/tmp/fifo_serv", O_RDONLY) ){
        while((n = read(fd, buffer, BUFFER)) != 0){
            if(fork() == 0){
                execl("ctrler", "ctrler", NULL);
                printf("Failed to execute exec!\n");
                exit(1);
            }
            else
            {
                printf("User %s initializing work...\n", buffer);
            }
        }
        close(fd);
    }
    return 0;
}