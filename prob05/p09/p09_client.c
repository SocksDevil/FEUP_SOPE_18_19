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
    int pid = getpid();
    sprintf(buffer, "%d %d", pid, argv[1]);
    printf("PID: %d", pid);
    mkfifo("/tmp/fifo.s", 0660);
    fd = open("/tmp/fifo.s", O_WRONLY);
    // write(fd, &pid, 500);
    write(fd, buffer, strlen(buffer));
    close(fd);
    char * fifo = "/tmp/fifo.";
    sprintf(buffer, "%s%d", fifo, pid);
    fd = open(buffer, O_RDONLY);
    n = read(fd, buffer, 500);
    write(STDOUT_FILENO, buffer, n);
    return 0;
}