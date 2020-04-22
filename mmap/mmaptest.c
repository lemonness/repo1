#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<pthread.h>
#include<fcntl.h>
#include <sys/mman.h>
#include <unistd.h>



void sys_err (const char * msg)
{
    perror(msg);
    exit(1);
}

int main(int argc ,char* argv[])
{
    char *p =NULL;
    int fd;

    fd = open("testmap.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd == -1){
        sys_err("fail to creak fd");
    }

    ftruncate(fd,4097);
    int len = lseek(fd,0,SEEK_END);
    p =mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,4096);

    if(p == MAP_FAILED){
        sys_err("mmap error");
    }
    strcpy(p,"hello mmap");
    printf("-----------%s\n",p);

    int ret = munmap(p,len);
    if(ret==-1){
        sys_err("munmap error");
    }
    close(fd);
    return 0;
}
