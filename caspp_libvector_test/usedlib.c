#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>

/* Use dynamic lib libvector.so   use gcc -o prog21 usedlib.c ./libvetctor.so*/
int x[2]={1,2};
int y[2]={3,4};
int z[2];

int main(){
    addvec(x,y,z,2);
    printf("z=[%d %d]\n",z[0],z[1]);
    multvec(x,y,z,2);
    printf("z=[%d %d]\n",z[0],z[1]);
    
    return 0;

}