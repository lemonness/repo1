#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void main(int argc, char *argv[])
{
    int * a = 4;
    printf("int* :%d\n",sizeof(a) );
    printf("Before the child generate-----------\n");
    printf("Before the child generate-----------\n");
    printf("Before the child generate-----------\n");

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork error");
        exit(1);
    }else if (pid == 0)  {
        printf("this is child thread  ,number is %d, parent pid is %d\n", getpid(), getppid());
    }else if (pid > 0)  {
        printf("this is parent thread , numberis %d, ,my child thread is %d,my parent pid is %d\n", getpid(), pid,getppid());
    }

    printf("fork is over\n");
}
