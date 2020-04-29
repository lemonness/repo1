#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>

int var =10;
void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}
void* tfn(void *arg){
    var =200;
    printf("this is  child thread var = %d\n",var);
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret =pthread_create(&tid,NULL,tfn,NULL);
    if(ret!=0)
        sys_err("pthread error");

    sleep(1);
       printf("this is main thread var = %d\n",var);
    return 0;
}