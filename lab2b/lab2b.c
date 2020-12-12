#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc,char* argv[]){
	int r_fd,w_fd;
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
                int pData[2];
                pData[0] = getpid();
                time_t pt = time(NULL);
                pData[1] = gmtime(&pt)->tm_sec;
                w_fd = open("./file",O_WRONLY);
                if(w_fd < 0){
                        perror("open fifo for write");
                        exit(-1);
                }

                write(w_fd,pData,sizeof(pData));
                close(w_fd);
                exit(0);
	}
	else{
		sleep(5);
		int cData[2];
                time_t ct = time(NULL);
                r_fd = open("./file",O_RDONLY);
                if(r_fd < 0){
                        perror("open fifo for read");
                        exit(-1);
                }
                if(read(r_fd,cData,sizeof(cData)) > 0){
                        time_t ct = time(NULL);
                        printf("Child process with time = %d gets data from Parent process with pid = %d and with time = %d\n",gmtime(&ct)->tm_sec - startTime,cData[0],cData[1] - startTime);
                }
                close(r_fd);
                exit(0);
	}
	return 0;
}
