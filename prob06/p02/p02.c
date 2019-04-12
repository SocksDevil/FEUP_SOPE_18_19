// PROGRAMA p01.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define STDERR 2
#define NUMITER 10000

int num_prints = NUMITER;


void * thrfunc(void * arg)
{
    int i;
    fprintf(stderr, "Starting thread %s\n", (char *) arg);
    for (i = 1; i <= num_prints; i++){ 
        write(STDERR,arg,1);
        num_prints--;
    }
    int* return_value = malloc(sizeof(int));
    *return_value = i;
    return return_value;
}
int main()
{
    pthread_t ta, tb;
    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");
    int * a, * b;
    pthread_join(ta, (void **) &a);
    pthread_join(tb, (void ** ) &b);
    printf("\nThread 1: %d, Thread 2: %d\n", *a, *b);
    return 0;
}