#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

struct arguments
{
    pid_t pid;
    char * argv;
};



int main(int argc, char ** argv){
    int n, fd;
    char buffer[500];
    struct arguments args;
    ++argv;
    args.argv = malloc(sizeof(argv));
    // for(int i = 0; i < 20; i++){
    //     if(argv[i] == NULL){
    //         args.argv[i] = NULL;
    //         break;
    //     }
    //     args.argv[i] = argv[i];
    //     printf("Argument: %s\n", args.argv[i]);
    // }
    strcpy(args.argv, argv[0]);
    printf("Argument: %s", args.argv);
    args.pid = getpid();
    fd = open("/tmp/fifo.s", O_WRONLY);
    write(fd,&args, sizeof(args));
    write(fd, buffer, strlen(buffer));
    close(fd);
    char * fifo = "/tmp/fifo.";
    sprintf(buffer, "%s%d", fifo, args.pid);
    mkfifo(buffer, 0660);
    fd = open(buffer, O_RDONLY);
    n = read(fd, buffer, 500);
    write(STDOUT_FILENO, buffer, n);
    return 0;
}