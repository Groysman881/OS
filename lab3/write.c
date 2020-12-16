#include<sys/types.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

char* data;
void stop(int signal){
	data[0] = '0';
	exit(0);
}

int main(int argc,char* argv[]){
	key_t key;
	signal(SIGINT,stop);
	pid_t pid = getpid();
	int fd;
	time_t t = time(NULL);
	key = ftok("./shmemory",'a');
	if((key == -1)){
		perror("ftok");
		exit(-1);
	}
	fd = shmget(key,64, 0666 | IPC_CREAT);
	if(fd == -1){
		perror("shmget");
		exit(-1);
	}
	data = shmat(fd,NULL,0);
	if(data == (char*)(-1)){
		perror("shmat");
		exit(-1);
	}
	if(data[0] == '1'){
		printf("Some process already writes\n");
		exit(0);
	}
	while(1){
		sprintf(data,"1pid = %d, time = %d : %d : %d",pid,gmtime(&t)->tm_hour,gmtime(&t)->tm_min,gmtime(&t)->tm_sec);
		sleep(1);
	}

	return 0;
}
