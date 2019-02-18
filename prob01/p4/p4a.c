#include <stdio.h>
int main(void)
{
    printf("Insert your name\n");
    char name[20];
    scanf("%s", name);
    printf("Hello %s!", name);
    return 0;
} 