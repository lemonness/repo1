#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include<string.h>

struct student{
    int id;
    char  name[20];
};

void sys_err(const char *msg)
{
    perror(msg);
    exit(1);
}
void* tfn(void *arg){
    struct student *sval;
    sval =(struct student *)arg;
    sval->id=15;
    strcpy(sval->name,"Edaward");
    return sval;
}

int main()
{
    pthread_t tid;
    struct student *resval;
    struct student arg;
    int ret =pthread_create(&tid,NULL,tfn,(void *)&arg);
    if(ret!=0)
        sys_err("pthread error");

    ret = pthread_join(tid,(void **)&resval);

    //两个变量的地址是一样的
    printf("wait child ends , id= %d , name=%s,resval pointer=%p\n",resval->id,resval->name,resval);
    printf("mian thread struct id =%d ,name=%s,arg printer=%p\n",arg.id,arg.name,&arg);
    return 0;
}