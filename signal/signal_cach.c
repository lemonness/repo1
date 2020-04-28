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

void prt_catch(int signo){
    printf("catch SIGINT signal %d\n",signo);
}

int main(){
    signal(SIGINT,prt_catch);

    while(1);
}