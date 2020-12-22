#include<sys/types.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>


char buf[4];
char* data;
pthread_mutex_t mtx;
int counter = 0;
pthread_t tid[11];

void* tWrite(void* arg){
	while(1){
		pthread_mutex_lock(&mtx);
		counter++;
		sprintf(buf,"%d",counter);
		strcat(data,buf);
		pthread_mutex_unlock(&mtx);
		sleep(rand()%3+1);
	}	
}

void* tRead(void* arg){
	sleep(1);
	while(1){
		pthread_mutex_lock(&mtx);
		printf("tid of reading thread = %lld data from writing thread = %s\n",pthread_self(),data);
		pthread_mutex_unlock(&mtx);
		sleep(1);
	}
}

int main(int argc,char* argv[]){
	srand(time(NULL));
	data = (char*)malloc(150);
	if(pthread_mutex_init(&mtx,NULL) != 0){
		perror("mutex init");
		exit(-1);
	}
	int create = pthread_create(tid,NULL,tWrite,NULL);
	if(create != 0){
		perror("create");
		exit(-1);
	}
	for(int i = 1;i < 11;i++){
		create = pthread_create(tid+i,NULL,tRead,NULL);
		if(create != 0){
			perror("create");
			exit(-1);
		}
	}
	for(int i = 0;i < 11;i++){
		pthread_join(tid[i],NULL);
	}
	pthread_mutex_destroy(&mtx);

	return 0;
}

