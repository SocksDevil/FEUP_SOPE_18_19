#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>


#define BUFFER 500

struct numbers {
    int sum;
    int diff;
    float divis;
    int mult;
    pid_t pid;
};

void * send_info(void * arg){
    int fd2;
    struct numbers num = * (struct numbers *) arg;
    char answer_fifo[BUFFER];
    sprintf(answer_fifo, "/tmp/fifo_ans_%u", num.pid);
    printf("Opening fifo %s\n", answer_fifo);
    fd2 = open(answer_fifo, O_WRONLY);
    write(fd2, &num, BUFFER);
    return NULL;
}

int main(void) {
    int fd1;
    int first, second;
    struct numbers num;
    mkfifo("/tmp/fifo_req", 0660);
    while(1){
        fd1 = open("/tmp/fifo_req", O_RDONLY);
        pthread_t tid;
        pid_t pid;
        read(fd1, &first, BUFFER);
        read(fd1, &second, BUFFER);
        read(fd1, &pid, BUFFER);
        if(first == 0 && second == 0){
            printf("Received both 0's, shutting down\n");
            exit(0);
        }
        num.sum = first + second;
        num.diff = first - second;
        num.mult = first * second;
        num.divis = first/(double) second;
        struct numbers* sending_numbers = malloc(sizeof(num));
        *sending_numbers = num;
        sending_numbers->pid = pid;
        char answer_fifo[BUFFER];
        sprintf(answer_fifo, "/tmp/fifo_ans_%u", pid);
        pthread_create(&tid, NULL, send_info, sending_numbers);
        close(fd1);
    }
    return 0;
}