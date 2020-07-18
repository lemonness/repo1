#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<error.h>
#include<sys/wait.h>
#include<pthread.h>

void main(int argc ,char * argv[]){
	int fd[2];
	pid_t pid;
	int i =0;

	pipe(fd);
	for(i=0;i<2;i++){
		pid=fork();
		if(pid == 0)
			break;
	};

	if(i ==2){
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}else if(i==1){
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
	}else if(i==0){
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		execlp("wc","wc","-l",NULL);
	}

}

