#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void * sum(void * arg){
    int * arguments = (int *) arg;
    int * value = malloc(sizeof(int));
    *value = arguments[0] + arguments[1];
    return value;
}

void * diff(void * arg){
    int * arguments = (int *) arg;
    int * value = malloc(sizeof(int));
    *value = arguments[0] - arguments[1];
    return value;
}

void * mult(void * arg){
    int * arguments = (int *) arg;
    int * value = malloc(sizeof(int));
    *value = arguments[0] * arguments[1];
    return value;
}

void * division(void * arg){
    int * arguments = (int *) arg;
    int * value = malloc(sizeof(int));
    *value = arguments[0] / arguments[1];
    return value;
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
    int * value;
    pthread_join(tsum, (void **)&value);   
    printf("Sum : %d\n", *value); 
    pthread_join(tdiff, (void **)&value);    
    printf("Diff : %d\n", *value); 
    pthread_join(tmult, (void **)&value);    
    printf("Mult : %d\n", *value); 
    pthread_join(tdivi, (void **)&value);    
    printf("Divi : %d\n", *value); 
    return 0;
}