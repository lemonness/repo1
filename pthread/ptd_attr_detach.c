#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

void *fun1()
{
    printf("I am child thread ,id =%d,tid=%lu\n", getpid(), pthread_self());
    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_attr_t attr; //声明一个线程属性变量
    int res;
    res = pthread_attr_init(&attr); //初始化线程属性
    if (res != 0)
    {
        fprintf(stderr, "attr_init error:%s\n", strerror(res));
        exit(1);
    }
    res = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);      //设置线程舒心为分离属性
    if (res != 0)
    {
        fprintf(stderr, "attr_setdetachstate error:%s\n", strerror(res));
        exit(1);
    }

    res = pthread_create(&tid, &attr, fun1, NULL);      //创建线程时，讲线程属性的地址传入，创建好的线程就是默认线程分离状态
    if (res != 0)
    {
        fprintf(stderr, "pthread_create error:%s\n", strerror(res));
        exit(1);
    }
    res = pthread_attr_destroy(&attr);      //销毁线程属性
    if (res != 0)
    {
        fprintf(stderr, "pthread_destroy error:%s\n", strerror(res));
        exit(1);
    }

    res = pthread_join(tid, NULL);      //阻塞等待回收目标线程，由于设置了分离太，自动结束，join出错
    if (res != 0)
    {
        fprintf(stderr, "pthread_join error:%s\n", strerror(res));
        exit(1);
    }
    printf("main:pid =%d , tid =%lu\n", getpid(), pthread_self());
    pthread_exit((void *)0);
}