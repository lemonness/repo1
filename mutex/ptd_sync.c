#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

pthread_mutex_t mutex; //定义一把互斥锁

void *fun1()
{
    srand(time(NULL));
    while (1)
    {
        pthread_mutex_lock(&mutex);     //加锁
        printf("hello ");
        sleep(rand() % 3);          //模拟长时间操作共享资源，导致cpu易主，产生与时间有关的错误
        printf("world \n");
        pthread_mutex_unlock(&mutex);   //解锁
        sleep(rand() % 3);                  //注意，这里解锁完需要随机休息一会，否则解锁后直接调到循环开始加锁，导致其他线程无法操作共享资源
    }
}

int main()
{
    pthread_t tid;
    srand(time(NULL));
    int res;

    res = pthread_mutex_init(&mutex, NULL);     //初始化一把锁，将锁结构的地址传入
    if (res != 0)
    {
        fprintf(stderr, "mutex init error:%s\n", strerror(res));
        exit(1);
    }
    if ((res = pthread_create(&tid, NULL, fun1, NULL)) != 0)
    {
        fprintf(stderr, "pthread create error:%s\n", strerror(res));
        exit(1);
    }
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("HELLO ");
        sleep(rand() % 3);
        printf("WORLD \n");
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }

    pthread_join(tid, NULL);
    pthread_mutex_destroy(&mutex);
}