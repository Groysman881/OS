#include<sys/types.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<sys/sem.h>


int main(int argc,char* argv[]){
	
        int fd,sid;
        key_t key,skey;
        time_t t;
        char* data;
	struct sembuf v = {0,1,0};
	struct sembuf p = {0,-1,0};

        key = ftok("./shmemory",'a');
	skey = ftok("./sem",'a');
        if(key == -1 || skey == -1){
         	perror("ftok");
                exit(-1);
        }
        fd = shmget(key,64,IPC_EXCL);
        if(fd == -1){
                perror("shmget");
                exit(-1);
        }
	sid = semget(skey,1,IPC_EXCL);
	if(sid == -1){
		perror("semget");
		exit(-1);
	}
        data = shmat(fd,NULL,0);
        if(data == (char*)(-1)){
                perror("shmat");
                exit(-1);
        }
	if(data[0] == '0'){
		printf("Nothing to read");
		exit(-1);
	}
        while(1){
		if(semop(sid,&p,1) == -1){
			perror("semop");
			exit(-1);
		}
                t = time(NULL);
                printf("time of reading process = %d : %d : %d info about writing process: %s\n",gmtime(&t)->tm_hour,gmtime(&t)->tm_min,gmtime(&t)->tm_sec,data+1);
                //sleep(1);
		if(semop(sid,&v,1) == -1){
			perror("semop");
			exit(-1);
		}
		sleep(1);
        }

        return 0;
}

