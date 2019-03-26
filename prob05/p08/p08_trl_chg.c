#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define BUFFER  500

int messages;
void alarm_handler(int signo){
    printf("Leaving, read %d messages\n", messages);
    exit(0);
}

int main(void){
    int n, fd;
    char buffer[BUFFER];
    mkfifo("/tmp/fifo_chg", 0660);
    fd = open("/tmp/fifo_chg", O_RDONLY);
    struct sigaction action;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    action.sa_handler = alarm_handler;
    sigaction(SIGALRM, &action, NULL);
    alarm(20);
    char * message = "New message: ";
    while((n = read(fd, buffer, BUFFER))){
        write(STDOUT_FILENO, message, strlen(message));
        write(STDOUT_FILENO, buffer, n);
        write(STDOUT_FILENO, "\n", 1);
        messages++;
    }

    return 0;
}