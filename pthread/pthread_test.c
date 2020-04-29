#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>

int num ;

void *tfn(void *arg)
{
    num =20;
    sleep(1);
    printf("thread pid = %d ,  tid = %lu\n", getpid(), pthread_self());
    pthread_exit((void *)&num);    //pthread_exit()退出当前进程，无返回值，如果传值则由调用他的线程回收获得信息。
}

int main()
{
    pthread_t tid;
    int *resval;
    printf("main pid = %d ,  tid = %lu\n", getpid(), pthread_self());

    int res = pthread_create(&tid, NULL, tfn, NULL);

    res = pthread_join(tid, (void **)&resval);
    if (res != 0)
    {
        fprintf(stderr, "pthread_join error:%s\n", strerror(res));
        exit(1);
    }
    printf("wait child ends ,exit infom=%d\n", *resval);
    while (1)
        ;
    return 0;
}

// void sys_err(const char *msg)
// {
//     perror(msg);
//     exit(1);
// }
// void* tfn(void *arg){
//     printf("thread pid = %d ,  tid = %lu\n", getpid(), pthread_self());
//     return NULL;
// }

// int main()
// {
//     pthread_t tid;
//     printf("main pid = %d ,  tid = %lu\n", getpid(), pthread_self());

//     int ret =pthread_create(&tid,NULL,tfn,NULL);
//     if(ret!=0)
//         sys_err("pthread error");

//     // sleep(1);
//     pthread_exit(NULL); //只是退出主线程，但是子线程没有退出。如果是return，直接退出进程，导致子线程无法打印
//     return 0;
// }
