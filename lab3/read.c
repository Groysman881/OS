#include<sys/types.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>



int main(int argc,char* argv[]){
        int fd;
        key_t key;
        time_t t;
        char* data;
	key = ftok("./shmemory",'a');
        if(key == -1){
                perror("ftok");
                exit(-1);
        }
        fd = shmget(key,64,IPC_EXCL);
        if(fd == -1){
                perror("shmget");
                exit(-1);
        }
        data = shmat(fd,NULL,0);
        if(data == (char*)(-1)){
                perror("shmat");
                exit(-1);
        }
	if(data[0] != '1'){
		printf("Nothing to read\n");
		exit(0);
	}
        while(1){
                t = time(NULL);
                printf("time of reading process = %d : %d : %d info about writing process: %s\n",gmtime(&t)->tm_hour,gmtime(&t)->tm_min,gmtime(&t)->tm_sec,data+1);
	     	sleep(1);
        }

        return 0;
}

