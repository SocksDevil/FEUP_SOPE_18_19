#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ARGUMENTS 5000 
#define MAX_NAME      50

int main(int argc, char **argv, char **envp)
{
    printf("Hello %s!\n", getenv("USERNAME"));
    return 0;
} 