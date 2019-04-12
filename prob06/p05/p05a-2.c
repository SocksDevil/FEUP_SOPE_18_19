#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

struct arguments{
    int first_num;
    int second_num;
};

void * sum(void * arg){
    struct arguments *args = (struct arguments *) arg;
    printf("Sum: %d\n", args->first_num + args->second_num);
    return NULL;
}

void * diff(void * arg){
    struct arguments *args = (struct arguments *) arg;
    printf("Diff: %d\n", args->first_num - args->second_num);
    return NULL;
}

void * mult(void * arg){
    struct arguments *args = (struct arguments *) arg;
    printf("Mult: %d\n", args->first_num * args->second_num);
    return NULL;
}

void * division(void * arg){
    struct arguments *args = (struct arguments *) arg;
    printf("Division: %d\n", args->first_num / args->second_num);
    return NULL;
}

int main(){
    struct arguments * args = malloc(sizeof(struct arguments));
    pthread_t tsum, tdiff, tmult, tdivi;
    scanf("%d", &args->first_num);
    scanf("%d", &args->second_num);
    pthread_create(&tsum, NULL, sum, args);
    pthread_create(&tdiff, NULL, diff, args);
    pthread_create(&tmult, NULL, mult, args);
    pthread_create(&tdivi, NULL, division, args);
    pthread_exit(0);
}