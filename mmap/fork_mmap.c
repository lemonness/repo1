#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>


int var = 10;

void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int *p;
    pid_t pid;
    int fd;
    fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);

    ftruncate(fd, 4);

    p = (int *)mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == 0)
        sys_err("mmap error");

    close(fd);
    pid = fork();
    if (pid == -1)
        sys_err("fork error");
    if (!pid)
    {
        *p = 2000;
        var = 100;
        printf("child,*p=%d, var= %d\n", *p, var);
    }
    else if (pid)
    {
        sleep(1);
        printf("parent,*p = %d, var =%d\n", *p, var);
        wait(NULL);
    }
    int ret = munmap(p, 4);
    if (ret == -1)
        sys_err("munmap error");
}
