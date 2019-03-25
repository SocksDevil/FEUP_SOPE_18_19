#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER 500

struct numbers {
    int sum;
    int diff;
    float divis;
    int mult;
};

int main(void) {
    int n, fd1, fd2;
    int first, second;
    struct numbers num;
    mkfifo("/tmp/fifo_req", 0660);
    fd1 = open("/tmp/fifo_req", O_RDONLY);
    fd2 = open("/tmp/fifo_ans", O_WRONLY);
    n = read(fd1, &first, BUFFER);
    n = read(fd1, &second, BUFFER);
    num.sum = first + second;
    num.diff = first - second;
    num.mult = first * second;
    num.divis = first/(double) second;
    write(fd2, &num, BUFFER);
    close(fd1);
    close(fd2);
    return 0;
}