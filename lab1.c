#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void func(){
	puts("atexit!\n");
	return;
}

int main(int argc,char* argv[]){
	pid_t procID;
        procID = fork();
	int exFunc = atexit(func);
	if(exFunc == 0){
	
	}
	if(procID > 0){
		wait(NULL);
	}
	else if(procID == 0){
		printf("Child proccess with pid = %d and ppid = %d\n", getpid(),getppid());
		exit(0);
	}
	else{
		write(2,"Error!",7);
	}
	printf("Parent proccess with pid  = %d and ppid = %d\n", getpid(),getppid());	
	return(0);
}

