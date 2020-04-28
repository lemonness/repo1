#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int val = 10;
char buf[20];


void test(){
    printf("这是test测试程序");
    strcpy(buf,"test1 test");
    printf("test函数结果var=%d,buf=%s\n",val,buf);
}