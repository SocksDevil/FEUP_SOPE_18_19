// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
    printf("Hello from thread no. %d!\n", *(int *) threadnum);
    pthread_exit(NULL);
}


int main()
{
    pthread_t threads[NUM_THREADS];
    int t;
    int threads_numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(t=0; t< NUM_THREADS; t++){
        printf("Creating thread %d\n", t);
        pthread_create(&threads[t], NULL, PrintHello, (void *)&threads_numbers[t]);
    }
    pthread_exit(0);
}