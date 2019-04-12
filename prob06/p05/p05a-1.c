#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void * sum(void * arg){
    int * arguments = (int *) arg;
    printf("Sum: %d\n", arguments[0] + arguments[1]);
    return NULL;
}

void * diff(void * arg){
    int * arguments = (int *) arg;
    printf("Diff: %d\n", arguments[0] - arguments[1]);
    return NULL;
}

void * mult(void * arg){
    int * arguments = (int *) arg;
    printf("Mult: %d\n", arguments[0] * arguments[1]);
    return NULL;
}

void * division(void * arg){
    int * arguments = (int *) arg;
    printf("Division: %d\n", arguments[0] / arguments[1]);
    return NULL;
}

int main(){
    int arguments[2];
    pthread_t tsum, tdiff, tmult, tdivi;
    scanf("%d", &arguments[0]);
    scanf("%d", &arguments[1]);
    pthread_create(&tsum, NULL, sum, arguments);
    pthread_create(&tdiff, NULL, diff, arguments);
    pthread_create(&tmult, NULL, mult, arguments);
    pthread_create(&tdivi, NULL, division, arguments);
    pthread_exit(0);
}