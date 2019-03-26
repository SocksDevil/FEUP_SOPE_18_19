#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


int main(int argc, char * argv[]){
    int n, fd;
    char buffer[500];
    fd = open("/tmp/fifo_serv", O_WRONLY);
    write(fd, argv[1], strlen(argv[1]));
    close(fd);
    fd = open("/tmp/fifo_chg", O_WRONLY);
    while(scanf("%s", buffer)){
        write(fd, buffer, strlen(buffer));
    }
}