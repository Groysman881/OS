#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc,char* argv[]){
	int fd;
	time_t start = time(NULL);
	int startTime = gmtime(&start)->tm_sec;
	pid_t procID;
	unlink("./file");
	int fifo = mkfifo("./file",0777);
	if(fifo == -1){
		perror("fifo");
		exit(-1);
	}
	procID = fork();
	if(procID < 0){
		perror("fork");
		exit(-1);
	}
	if(procID > 0){
                int pData[4];
                pData[0] = getpid();
                time_t pt = time(NULL);
                pData[1] = gmtime(&pt)->tm_hour;
		pData[2] = gmtime(&pt)->tm_min;
		pData[3] = gmtime(&pt)->tm_sec;
                fd = open("./file",O_WRONLY);
                if(fd < 0){
                        perror("open fifo for write");
                        exit(-1);
                }

                write(fd,pData,sizeof(pData));
                close(fd);
                exit(0);
	}
	else{
		sleep(5);
		int cData[4];
                time_t ct = time(NULL);
                fd = open("./file",O_RDONLY);
                if(fd < 0){
                        perror("open fifo for read");
                        exit(-1);
                }
                if(read(fd,cData,sizeof(cData)) > 0){
                        time_t ct = time(NULL);
                        printf("Child process with time = %d : %d : %d gets data from Parent process with pid = %d and with time = %d : %d : %d\n",gmtime(&ct)->tm_hour,gmtime(&ct)->tm_min,gmtime(&ct)->tm_sec,cData[0],cData[1],cData[2],cData[3]);
                }
                close(fd);
                exit(0);
	}
	return 0;
}
