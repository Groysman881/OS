#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(int argc,char* argv[]){
	time_t t = time(NULL);
	int startTime = gmtime(&t)->tm_sec;
	int fd[2];
        pid_t procID;
	if(pipe(fd) == -1){
		perror("pipe");
		exit(-1);
	}

	procID = fork();
	
	if(procID == -1){
		perror("fork");
		exit(-1);
	}
	if(procID == 0){
		close(fd[1]);
		int buf[2];
		time_t ct = time(NULL);
		int childTime = gmtime(&ct)->tm_sec;
		printf("Child proccess with time = %d gets ",childTime - startTime);
		if(read(fd[0],buf,sizeof(buf))>0)
			printf("data from Parent proccess with pid = %d and with time = %d\n",buf[0],buf[1]- startTime);
		close(fd[0]);
		exit(0);
	}
	else{
                close(fd[0]);
		sleep(5);
		int data[2];
                data[0] = getpid();
		time_t pt = time(NULL);
		data[1] = gmtime(&pt)->tm_sec;
		write(fd[1],&data,sizeof(data));
                close(fd[1]);
                exit(0);
        }

	return 0;
}
