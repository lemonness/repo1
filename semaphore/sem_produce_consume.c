#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
 #include <semaphore.h>

#define NUM 5

int queue[NUM];
sem_t product_number, blank_number; //产品信号量和空格信号量

void err_thread(int ret, char *err)
{
    fprintf(stderr, "%s:%s\n", err, strerror(ret));
    pthread_exit(NULL);
}

void *produce(void *arg)
{
    int i = 0;
    while (1)
    {
        sem_wait(&blank_number);
        queue[i] = rand() % 1000 + 1;
        printf("----Produce---%d\n", queue[i]);
        sem_post(&product_number);
        i = (i + 1) % NUM;
        sleep(rand() % 1);
    }
    return NULL;
}

void *consume(void *arg)
{
    int i = 0;
    while (1)
    {
        sem_wait(&product_number);
        printf("--Consume--%d\n", queue [i]);
        queue[i] = 0;
        sem_post(&blank_number);
        i = (i + 1) % NUM;
        sleep(rand() % 3);
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t protid, contid;
    sem_init(&blank_number, 0, NUM);
    sem_init(&product_number, 0, 0);

    pthread_create(&protid, NULL, produce, NULL);
    pthread_create(&contid, NULL, consume, NULL);

    pthread_join(protid, NULL);
    pthread_join(contid, NULL);

    sem_destroy(&blank_number);
    sem_destroy(&product_number);

    return 0;
}