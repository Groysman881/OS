#include<sys/types.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>

#define NUM_OF_THREADS 11


char buf[4];
char* data;
pthread_rwlock_t rwl;
int counter = 0;
pthread_t tid[NUM_OF_THREADS];

void* tWrite(void* arg){
 	while(1){
     		pthread_rwlock_wrlock(&rwl);
      		counter++;
     		sprintf(buf,"%d",counter);
    		strcat(data,buf);
     		pthread_rwlock_unlock(&rwl);
    		sleep(rand()%3+1);
  	}
}

void* tRead(void* arg){
	sleep(1);
    	while(1){
        	pthread_rwlock_rdlock(&rwl);
        	printf("tid of reading thread = %lx data from writing thread = %s\n",(long)pthread_self(),data);
        	pthread_rwlock_unlock(&rwl);
        	sleep(1);
	}
}

int main(int argc,char* argv[]){
	srand(time(NULL));
    	data = (char*)malloc(150);
    	if(pthread_rwlock_init(&rwl,NULL) != 0){
    		perror("rwlock init");
    		exit(-1);
    	}
   	int create = pthread_create(tid,NULL,tWrite,NULL);
  	if(create != 0){
 		perror("create");
   		exit(-1);
    	}
   	for(int i = 1;i < NUM_OF_THREADS;i++){
    		create = pthread_create(tid+i,NULL,tRead,NULL);
       		if(create != 0){
        		perror("create");
        		exit(-1);
		}
 	}
    	for(int i = 0;i < NUM_OF_THREADS;i++){
    		pthread_join(tid[i],NULL);
    	}
	pthread_rwlock_destroy(&rwl);
	return 0;
}

