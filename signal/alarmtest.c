#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}

void main(int argc, char *argv[])
{
    int i = 1;
    alarm(1);

    while (1)
    {
        printf("i = %d\n", i);
        i++;
    }
}