#include <stdio.h>
#include<string.h>
#define ALLOCSIZE 1000 /* size of available space */

static char allocbuff[ALLOCSIZE];
static char* allocp=allocbuff;

char * alloc(int n){
    if(allocbuff+ALLOCSIZE-allocp>=n)
        allocp+=n;
    else    
        return 0;
}
void afree(char * p){
    if(p>=allocbuff&&p<allocbuff+ALLOCSIZE)
    allocp=p;
}
int mystrlen(char * s){
    char * p =s;
    while(*p !='\0')
        p++;
    return p-s;
}

int mystrcmp(char*p,char*s){
	for(;*p==*s;p++,s++)
		if(*p =='\0')
			return 0;
	return *p - *s;			
}

int main()
{
    char * a1 ="Hello";
    char * a2 ="He";
    char *p;
    int charnum;
    p = alloc(800);
    // q = alloc(300);
    strcpy(p,"hello,alloc");
    charnum = mystrlen(p);
    // printf("p=%p, q=%p\n", p, q);
        printf("p=%p, charnum=%d\n", p, charnum);
    afree(p);

    printf("两个字符串的比较结果%d\n",mystrcmp(a1,a2));
}