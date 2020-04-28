#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include<signal.h>
#include <sys/time.h>


void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}
void myfunc(int signo)
{
    printf("Hello World \n");
}

void main(int argc, char *argv[])
{
    struct itimerval it , oldit;
    signal(SIGALRM,myfunc);
    it.it_value.tv_sec = 2;
    it.it_value.tv_usec = 0;

    it.it_interval.tv_sec =4;
    it.it_interval.tv_usec = 0;
    if(setitimer(ITIMER_REAL,&it,&oldit)==-1)
        sys_err("setitimer error");
    while(1);

}