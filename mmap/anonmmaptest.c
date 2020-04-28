#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>


void sys_err (const char * msg)
{
    perror(msg);
    exit(1);
}

void main(int argc ,char* argv[])
{
    int *p =NULL;
    pid_t pid ;
    int var = 10;

    p =(int *)mmap(NULL,50,PROT_READ|PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,-1,0);

    if(p == MAP_FAILED){
        sys_err("mmap error");
    }
    pid = fork();
    if(pid ==-1)
        sys_err("fork error");
    if(!pid){
        *p = 1000;
        var =100;
        printf("this is child thread *p=%d, var = %d\n",*p,var);
    }else if(pid){
        sleep(1);
        printf("this is parent thread *p=%d, var = %d\n",*p,var);
        wait(NULL);
    }

}
