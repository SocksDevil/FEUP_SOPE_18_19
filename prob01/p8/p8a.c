#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

#define MAX_ITER     10000

int main(int argc, int **argv)
{
    time_t t;
    srand((unsigned) time(&t));
    struct tms time_info;
    int ticks_seg = sysconf(_SC_CLK_TCK);
    times(&time_info);


    printf("Initial time %d, with %d cpu ticks", time_info.tms_utime/ticks_seg, time_info.tms_utime);
    if(argc != 3)
    {
        printf("Wrong number of arguments\n");
        return 1;
    }
    for (int i = 0; i < MAX_ITER; i++)
    {
        int random = rand() % atoi(argv[1]);

        if(random == atoi(argv[2]))
            break;
        printf("%d: %d at %d\n", i, random);
    }
    printf("End time %d, with %d cpu ticks", time_info.tms_utime/ticks_seg, time_info.tms_utime);
    return 0;
}