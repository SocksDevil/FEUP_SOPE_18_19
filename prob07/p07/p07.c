#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_ITEMS 200
#define NUM_DATA 4

sem_t empty, full;
struct file_info* data[NUM_DATA] = {NULL};
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // mutex p/a sec.critica

struct file_info {
  struct dirent direntp;
  struct stat stat_buf;
  char *buffer;
};

void *copy_file(void *arg) {
  struct file_info *info = (struct file_info *)arg;
  printf("Copying file %s to %s\n", info->direntp.d_name, info->buffer);
  char command[BUFSIZ];
  if (S_ISREG(info->stat_buf.st_mode)) {
    sprintf(command, "cp %s %s", info->direntp.d_name, info->buffer);
    system(command);
  } else if (S_ISDIR(info->stat_buf.st_mode)) {
    if (strstr(info->direntp.d_name, ".") == NULL &&
        strstr(info->direntp.d_name, "..") == NULL) {
      sprintf(command, "mkdir %s %s", info->direntp.d_name, info->buffer);
      system(command);
    }
  }
  pthread_exit(0);
}

void push_data(struct file_info * saving_data) {
    for (int i = 0; i < NUM_DATA; i++) {
        if (data[i] == NULL) {
        data[i] = saving_data;
        return;
        }
    }
    printf("Data not pushed\n");
}

struct file_info * retrieve_data() {
    for (int i = 0; i < NUM_DATA; i++) {
        if (data[i] != NULL) {
        struct file_info * retrieved = data[i];
        data[i] = 0;
        return retrieved;
        }
    }
    return NULL;
}

void *producer(void *arg) {
    struct file_info * info = (struct file_info *) arg;
    sem_wait(&empty);
    pthread_mutex_lock(&mut);
    push_data(info);
    pthread_mutex_unlock(&mut);
    sem_post(&full);
    pthread_exit(0);
    printf("Finished pushing data\n");
}

void *consumer(void *arg) {
  printf("New consumer running!\n");
  for (int i = 0; i < 49; i++) {
    int value;
    struct file_info * info;
    sem_getvalue(&full, &value);
    sem_wait(&full);
    pthread_mutex_lock(&mut);
    info = retrieve_data();
    pthread_mutex_unlock(&mut);
    sem_post(&empty);
    if(info == NULL){
        break;
    }
    copy_file(info);
  }
  pthread_exit(0);
}


int main(int argc, char *argv[])
{
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    char buffer[512];

    sem_init(&empty, 0, NUM_DATA);
    sem_init(&full, 0, 0);

    if ((dirp = opendir( argv[1])) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }

    pthread_t tid;

    for (int i = 0; i < 4; i++) {
        pthread_create(&tid, NULL, consumer, NULL);
    }
    getcwd(buffer, 512);
    if(argv[2][0] == '.')
        strcat(buffer, argv[2]);
    strcat(buffer, "/");
    strcat(buffer, argv[2]);
    printf("Path: %s\n", buffer);
    chdir(argv[1]);
    while ((direntp = readdir( dirp)) != NULL)
    {
        if(stat(direntp->d_name, &stat_buf) == 0){
            struct file_info * info = malloc(sizeof(struct file_info));
            info->direntp = *direntp;
            info->stat_buf = stat_buf;
            info->buffer = buffer;
            pthread_create(&tid, NULL, producer, info);
        }
    }
    pthread_create(&tid, NULL, producer, NULL);
    closedir(dirp);
    pthread_exit(0);
}
