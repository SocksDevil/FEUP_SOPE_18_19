#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER 512
#define READ    0
#define WRITE   1

int main(void){
    int n, fd[2];
    pid_t pid;
    pipe(fd);
    int first, second;
    char line[BUFFER];

    if(fork() > 0){
        close(fd[READ]);
        printf("Write two numbers: \n");
        scanf("%d", &first);        
        scanf("%d", &second);
        write(fd[WRITE], &first, sizeof(first));        
        sprintf(line, "%d", second);
        write(fd[WRITE], &second, sizeof(second));        
    }
    else{
        close(fd[WRITE]);
        n = read(fd[READ], &first, BUFFER);
        n = read(fd[READ], &second, BUFFER);
        int sum = first + second;
        int diff = first - second;
        double division = first/(double) second;
        int mult = first * second;
        printf("Sum: %d, Difference: %d, Division: %f, Multiplication: %d\n", sum, diff, division, mult);
    }
    
}