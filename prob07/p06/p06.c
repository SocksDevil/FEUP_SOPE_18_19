#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_ITEMS 200
#define NUM_DATA 4

int empty, full;
int data[NUM_DATA] = {0};
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // mutex p/a sec.critica
pthread_cond_t empty_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t full_cond = PTHREAD_COND_INITIALIZER;

void push_data(int saving_data) {
  for (int i = 0; i < NUM_DATA; i++) {
    if (data[i] == 0) {
      data[i] = saving_data;
      return;
    }
  }
  printf("Data not pushed\n");
}

int retrieve_data() {
  for (int i = 0; i < NUM_DATA; i++) {
    if (data[i] != 0) {
      int retrieved = data[i];
      data[i] = 0;
      return retrieved;
    }
  }
  return -1;
}

void *producer(void *arg) {
  int total = 0;
  for (int producing = 1; producing < NUM_ITEMS; producing++) {
    printf("Producer iteration %d\n", producing);
    pthread_mutex_lock(&mut);
    while(empty == 0){
        printf("Empty==0, waiting..,\n");
        pthread_cond_wait(&empty_cond, &mut);
    }
    empty--;
    push_data(producing);
    total += producing;
    full++;
    pthread_cond_signal(&full_cond);
    pthread_mutex_unlock(&mut);
  }
  printf("Total value produced %d\n", total);
  pthread_exit(0);
}

void *consumer(void *arg) {
  int data = 0;
  printf("New consumer running!\n");
  for (int i = 0; i < 49; i++) {
    pthread_mutex_lock(&mut);
    while (full == 0) {
      printf("Full==0, waiting..,\n");
      pthread_cond_wait(&full_cond, &mut);
    }
    full--;
    data += retrieve_data();
    empty++;
    pthread_cond_signal(&empty_cond);
    pthread_mutex_unlock(&mut);
  }
  printf("Consumed %d of data\n", data);
  pthread_exit(0);
}

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, producer, NULL);
  empty = NUM_DATA;
  full = 0;

  for (int i = 0; i < 4; i++) {
    pthread_create(&tid, NULL, consumer, NULL);
  }
  pthread_exit(0);
}