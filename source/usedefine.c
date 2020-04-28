#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#define dprint(expr) printf(#expr " = %d\n" , expr)

int main(){
    int x =4;
    int y =2;
    dprint(x/y);
    return 0;
}