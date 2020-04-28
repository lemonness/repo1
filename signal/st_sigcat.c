#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <signal.h>

void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}

void sig_catch(int signo)
{
    printf("catch sig %d\n", signo);
    return;
}
int main()
{
    struct sigaction act, oldact;
    act.sa_handler = sig_catch;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    int ret = sigaction(SIGINT, &act, &oldact);  //注册一个信号捕捉函数
    if (ret == -1)
        sys_err("sigaction error");
    ret = sigaction(SIGQUIT, &act, &oldact);
    if (ret == -1)
        sys_err("sigaction error");
    while (1)
        ;
    return 0;
}