#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<error.h>

void main(int argc ,char * argv[]){
	int i = 0;
	for(i=0;i<5;i++){
		if(fork()==0){
			break;
		}
	
	}
	if(i==5){
		sleep(5);
		printf("I am the parent thread\n");
	}else{
		sleep(i);
		printf("I am the %d child tread\n",i);
	}
}

