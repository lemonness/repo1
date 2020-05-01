#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

//线程错误处理函数
void err_thread(int ret, char *err)
{
    fprintf(stderr, "%s:%s\n", err, strerror(ret));
    pthread_exit(NULL);
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  //定义/初始化一个互斥量
pthread_cond_t has_data = PTHREAD_COND_INITIALIZER; //定义/初始化一个条件变量

struct msg
{
    int num;
    struct msg *next;
};

//定义一个头指针
struct msg *head;

//生产者函数
void *produce(void *arg)
{
    while (1)
    {
        struct msg *mp = malloc(sizeof(struct msg));

        mp->num = rand() % 1000 + 1; //生产一个数据
        printf("procude num %d \n", mp->num);

        pthread_mutex_lock(&mutex); //将数据挂到公共区域，此时先上锁
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_data); //发信号，通知其他线程
        sleep(rand() % 3);
    }
    return NULL;
}

void *consume(void *arg)
{
    while (1)
    {
        struct msg *mp; //创建一个msg结构体指针，由于要获得生产者生产的内容，所以不需要创建空间

        pthread_mutex_lock(&mutex);               //加锁 互斥量
        if (head == NULL)                         //判断是否有数据，没有的进入阻塞等待唤醒
            pthread_cond_wait(&has_data, &mutex); //解锁，阻塞等待，满足条件后枷锁

        mp = head; //消费数据
        head = mp->next;
        pthread_mutex_unlock(&mutex); //解锁
        printf("---------consumer num :%d\n", mp->num);
        sleep(rand() % 3);
        free(mp); //将生产者申请的内存空间释放
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    int ret;
    pthread_t propid, conpid;

    ret = pthread_create(&propid, NULL, produce, NULL);
    if (ret != 0)
        err_thread(ret, "propid pthread create error");
    ret = pthread_create(&conpid, NULL, consume, NULL);
    if (ret != 0)
        err_thread(ret, "conpid pthread create error");

    pthread_join(propid, NULL);
    pthread_join(conpid, NULL);
}