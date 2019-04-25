// PROGRAMA p01.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define MAXELEMS 10000000 // nr. max de posicoes
#define MAXTHREADS 100 // nr. max de threads
#define min(a, b) (a)<(b)?(a):(b)
#define SEM_NAME    "/sem05"

int npos;
int  * g_buf, pos=0, val=0; // variaveis partilhadas
void *fill(void *nr, int * buf, int * pos, sem_t * sem)
{
    while (1) {
        sem_wait(sem);
        printf("Reached count\n");
        if (pos[0] >= npos) {
            sem_post(sem);
            return NULL;
        }
    buf[pos[0]] = pos[1];
    pos[0]++; pos[1]++;
    sem_post(sem);
    *(int *)nr += 1;
    }
}


void *verify(void *arg)
{
    if(arg == NULL){
        int k;
        for (k=0; k<npos; k++)
            if (g_buf[k] != k) // detecta valores errados
            printf("ERROR: buf[%d] = %d\n", k, g_buf[k]);
        return NULL;
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    int k, nthr, count[MAXTHREADS]; // array para contagens
    pthread_t tidv; // tids dos threads
    int total;
    sem_t * sem;
    
    if (argc != 3) {
        printf("Usage: %s <nr_pos> <nr_thrs>\n",argv[0]);
        return 1;
    }
    int shmfd = shm_open("/shmp04", O_CREAT | O_RDWR, 0600);
    if(shmfd < 0){
        perror("Failure to open shared memory\n");
        exit(1);
    }

    if(ftruncate(shmfd, sizeof(int) * MAXELEMS) < 0){
        perror("Failed to allocate memory\n");
        exit(2);
    }

    int * buf = (int *) mmap(0, sizeof(int) * MAXELEMS, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    g_buf = buf;
    if(buf == MAP_FAILED){
        perror("Map failed!\n");
        exit(3);
    }

    int shmpos = shm_open("/shmp04_pos", O_CREAT | O_RDWR, 0600);
    if(shmpos < 0){
        perror("Failure to open shared memory\n");
        exit(1);
    }

    if(ftruncate(shmpos, sizeof(int) * 2) < 0){
        perror("Failed to allocate memory\n");
        exit(2);
    }

    int * pos = (int *) mmap(0, sizeof(int) * MAXELEMS, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if(pos == MAP_FAILED){
        perror("Map failed!\n");
        exit(3);
    }

    pos[0] = 0;
    pos[1] = 0;

    npos = min(atoi(argv[1]), MAXELEMS); //no. efectivo de posicoes
    nthr = min(atoi(argv[2]), MAXTHREADS); //no. efectivo de threads

    printf("npos, nthr: %d, %d\n", npos, nthr);
    sem = sem_open(SEM_NAME, O_CREAT, 0600, 1);

    if(sem == SEM_FAILED){
        perror("Failed to create semaphore!\n");
        exit(4);
    }

    for (k=0; k<nthr; k++) { // criacao das threads 'fill'
        count[k] = 0;
        if(fork() == 0){
            fill(&count[k], buf, pos, sem);
            exit(0);
        }
    }
    total=0;
    for (k=0; k<nthr; k++) { //espera threads 'fill'
        wait(NULL);
        printf("count[%d] = %d\n", k, count[k]);
        total += count[k];
    }
    printf("total count = %d\n",total); // mostra total
    pthread_create(&tidv, NULL, verify, NULL);
    pthread_join(tidv, NULL); // espera thread 'verify'
    sem_close(sem);
    sem_unlink(SEM_NAME);
    return 0;
}