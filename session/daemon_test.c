#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}
int main()
{
    pid_t pid;
    int res, fd;

    if ((pid = fork()) == -1)
        sys_err("fork error");

    if (pid > 0)
        exit(0);
    if ((pid = setsid()) == -1)
        sys_err("setsid  error");

    if ((res == chdir("/home/john")) == -1)
        sys_err("chdir error");
    if ((res == umask(0022)) == -1)
        sys_err("umask error");

    close(STDIN_FILENO);
    if ((fd = open("/dev/null", O_RDWR)) == -1)
        sys_err("open error");

    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    while (1)
        ;
    return 0;
}