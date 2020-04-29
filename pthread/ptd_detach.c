#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
//线程的出错处理和进程不一样，要用fprintf
void *fun1()
{
    printf("I am child thread ,id =%d,tid=%lu\n", getpid(),pthread_self());
    return NULL;
}

int main()
{
    pthread_t tid;
    int res;
    res = pthread_create(&tid, NULL, fun1, NULL);
    if (res != 0)
    {
        fprintf(stderr, "pthread_create error:%s\n", strerror(res));
        exit(1);
    }
    res = pthread_detach(tid);
    if (res != 0)
    {
        fprintf(stderr, "pthread_detach error:%s\n", strerror(res));
        exit(1);
    }

    sleep(1);
    res = pthread_join(tid, NULL);
    if (res != 0)
    {
        fprintf(stderr, "pthread_join error:%s\n", strerror(res));
        exit(1);
    }
    printf("main:pid =%d , tid =%lu\n", getpid(), pthread_self());
    pthread_exit((void *)0);
}