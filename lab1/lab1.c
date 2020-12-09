#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

void func(){
	printf("atexit in proccess with pid = %d\n",getpid());
	return;
}

int main(int argc,char* argv[]){
	pid_t procID;
	int exFunc = atexit(func);
        procID = fork();
	if(exFunc != 0){
		write(2,"Error",7);	
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

