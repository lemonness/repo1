#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}

void print_set(sigset_t *set)
{
    int i;
    for (i = 1; i <= 32; i++)
        if (sigismember(set, i))
            putchar('1');
        else
            putchar('0');
    printf("\n");
}

void catch_child(int signo)
{
    //查看是第几次调用该函数
    static int i;
    printf("第%d次回调该函数\n", ++i);
    pid_t wpid;
    int status;
    while ((wpid = waitpid(-1, &status, 0)) != -1) //循环回收，防止僵尸进程出现,一次回收所有子进程
    {
        if (WIFEXITED(status))
            printf("---------catch child id %d, ret =%d\n", wpid, WEXITSTATUS(status));
    }
    return;
}

int main()
{
    pid_t pid;
    sigset_t set, oldset, pedset;
    int res;

    //阻塞SIGCHLD信号
    if (sigaddset(&set, SIGCHLD) == -1)
        sys_err("sigaddset error");
    sigprocmask(SIG_BLOCK, &set, &oldset);

    int i;
    for (i = 0; i < 6; i++)
        if ((pid = fork()) == 0)
            break;

    //父进程执行操作
    if (i == 6)
    {
        printf("I'm parent pid ,my pid is %d\n", getpid());
        //模拟父进程在注册之前进行多部操作
        sleep(1);
        //查看未决信号集
        res = sigpending(&pedset);
        if (res == -1)
            sys_err("sigpending error");
        print_set(&pedset);

        //填充信号捕捉函数
        struct sigaction act;
        act.sa_handler = catch_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        //注册SIGCHLD信号
        sigaction(SIGCHLD, &act, NULL);
        //解除阻塞，否则回调函数没有执行的机会
        sigprocmask(SIG_UNBLOCK, &set, &oldset);
        //查看未决信号集
        if (sigpending(&pedset); == -1)
            sys_err("sigpending error");
        print_set(&pedset);

        while (1)
            ;
    }
    else
    {
        printf("I'm child pid ,my pid is %d\n", getpid());
        return i;
    }
}