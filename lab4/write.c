#include<sys/types.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/sem.h>


struct sembuf v = {0,1,0};
struct sembuf p = {0,-1,0};

char* data;
int sid,fd;

void stop(int signal){
	printf("\n");
	if(semctl(sid,0,IPC_RMID) == -1){
		perror("semctl");
		exit(-1);
	}
	struct shmid_ds* rm = NULL;
	shmctl(fd,IPC_RMID,rm);

        exit(0);
}

int main(int argc,char* argv[]){
	union semun sem;
        key_t key,skey;
        signal(SIGINT,stop);
        pid_t pid = getpid();
        time_t t;
	char* data;
        key = ftok("./shmemory",'a');
	skey = ftok("./sem",'a');
        if(key == -1){
                perror("ftok");
                exit(-1);
        }
	sid = semget(skey,1, 0666 | IPC_CREAT);
	if(sid == -1){
		perror("semget");
		exit(-1);
	}
	sem.val = 1;
	semctl(sid,0,SETVAL,sem);
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
		printf("Some process already writes");
		exit(-1);
	}
        while(1){
		if(semop(sid,&p,1) == -1){
			perror("semop");
			exit(-1);
		}
                t = time(NULL);
                sprintf(data,"1pid = %d, time = %d : %d : %d",pid,gmtime(&t)->tm_hour,gmtime(&t)->tm_min,gmtime(&t)->tm_sec);
                //sleep(1);
		if(semop(sid,&v,1) == -1){
			perror("semop");
			exit(-1);
		}
		sleep(1);
        }

        return 0;
}

