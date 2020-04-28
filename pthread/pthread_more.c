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
void *tfn(void *arg)
{
    int i = (int)arg;   // 强转
    printf("I am %dth thread ,pid = %d ,  tid = %lu\n", i + 1, getpid(), pthread_self());
    return NULL;
}

int main()
{
    printf("main pid = %d ,  tid = %lu\n", getpid(), pthread_self());
    int i;
    int ret;
    pthread_t tid;

    for (i = 0; i < 5; i++)
        if ((ret = pthread_create(&tid, NULL, tfn, (void *)i)) != 0)   //传参采用 值传递，借助强转
            sys_err("pthread error");

    sleep(1);
    return 0;
}
