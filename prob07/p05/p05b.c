#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NUM_ITEMS       200
#define NUM_DATA        4

sem_t empty, full;
int data[NUM_DATA] = {0};
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // mutex p/a sec.critica

void push_data(int saving_data){
    for(int i = 0; i < NUM_DATA; i++){
        if(data[i] == 0){
            data[i] = saving_data;
            return;
        }
    }
    printf("Data not pushed\n");
}

int retrieve_data(){
    for(int i = 0; i < NUM_DATA; i++){
        if(data[i] != 0){
            int retrieved = data[i];
            data[i] = 0;
            return retrieved;
        }
    }
    return -1;
}

void * producer(void * arg){
    int total = 0;
    for(int producing = 1; producing < NUM_ITEMS; producing++) {
        int value;
        sem_getvalue(&empty, &value);
        sem_wait(&empty);
        pthread_mutex_lock(&mut);
        push_data(producing);
        total+= producing;
        pthread_mutex_unlock(&mut);
        sem_post(&full);
    }
    printf("Total value produced %d\n", total);
    pthread_exit(0);
}

void * consumer(void * arg) {
    int data = 0;
    printf("New consumer running!\n");
    for (int i = 0; i < 49; i++){
      int value;
      sem_getvalue(&full, &value);
      sem_wait(&full);
      pthread_mutex_lock(&mut);
      data += retrieve_data();
      pthread_mutex_unlock(&mut);
      sem_post(&empty);
    }
    printf("Consumed %d of data\n", data);
    pthread_exit(0);
}

int main() {
    pthread_t tid;
    sem_init(&empty, 0, NUM_DATA);
    sem_init(&full, 0, 0);
    pthread_create(&tid, NULL, producer, NULL);

    for(int i = 0; i < 4; i++){
        pthread_create(&tid, NULL, consumer, NULL);
    }
    pthread_exit(0);
}