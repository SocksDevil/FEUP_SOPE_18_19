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
    char buffer[500], result[500];
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
    printf("Argument: %s\n", args.argv);
    args.pid = getpid();
    printf("PID: %d\n", args.pid);
    fd = open("/tmp/fifo.s", O_WRONLY);
    write(fd,&args.pid, sizeof(args.pid));
    write(fd, "ls", strlen("ls"));
    close(fd);
    char * fifo = "/tmp/fifo.";
    sprintf(buffer, "%s%d", fifo, args.pid);
    printf("Opening %s\n", buffer);
    mkfifo(buffer, 0660);
    fd = open(buffer, O_RDONLY);
    n = read(fd, result, 500);
    // write(STDOUT_FILENO, buffer, n);
    printf("Result: %s - n:%d\n", result, n);
    return 0;
}