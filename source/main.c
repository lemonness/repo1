#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include"test1.h"

int main()
{
    printf("调用test文件的函数\n");
    test();
    printf("调用main文件的函数\n");
    strcpy(buf, "main test");
    printf("main模块中结果var=%d,buf=%s\n", val, buf);
    return 0;
}