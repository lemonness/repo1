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
    sval = malloc(sizeof(struct student));
    sval->id=15;
    strcpy(sval->name,"Edaward");
    return sval;
}

int main()
{
    pthread_t tid;
    int ret =pthread_create(&tid,NULL,tfn,NULL);
    if(ret!=0)
        sys_err("pthread error");

    struct student *resval;
    ret = pthread_join(tid,(void **)&resval);
    printf("wait child ends , id= %d , name=%s\n",resval->id,resval->name);
    return 0;
}