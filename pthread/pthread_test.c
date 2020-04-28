#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>


void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}
void* tfn(void *arg){
    printf("thread pid = %d ,  tid = %lu\n", getpid(), pthread_self());
    return NULL;
}

int main()
{
    pthread_t tid;
    printf("main pid = %d ,  tid = %lu\n", getpid(), pthread_self());

    int ret =pthread_create(&tid,NULL,tfn,NULL);
    if(ret!=0)
        sys_err("pthread error");

    sleep(1);
    return 0;
}
