#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

int count = 0;
pthread_rwlock_t rwlock;

void *p_write(void *arg)
{
    int t;
    int  i = (int )arg;
     while (1)
    {
        pthread_rwlock_wrlock(&rwlock);
        t = count;
        usleep(1000);
        printf("=====write %d , tid=%lu, count= %d, ++count=%d\n",i, pthread_self(), t, ++count);
        pthread_rwlock_unlock(&rwlock);
        usleep(10000);
    }
    return NULL;
}
void *p_read(void *arg)
{
    int i = (int)arg;
    while (1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("=====read %d ,  tid=%lu, count= %d\n", i, pthread_self(), count);
        pthread_rwlock_unlock(&rwlock);
        usleep(2000);
    }
    return NULL;
}

int main()
{
    int i;
    pthread_t tid[8];
    pthread_rwlock_init(&rwlock, NULL);
    for (i = 0; i < 3; i++)
    {
        pthread_create(&tid[i], NULL, p_write, (void *)(i+1));
    }
    for (i = 3; i < 8; i++)
    {
        pthread_create(&tid[i], NULL, p_read, (void *)(i+1));
    }
    for (i = 0; i < 8; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_rwlock_destroy(&rwlock);
}