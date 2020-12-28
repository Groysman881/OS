#include<sys/types.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>

#define NUM_OF_THREADS 11
#define NUM_OF_READERS 10


char buf[4];
char* data;
int rdCounter = 0;
pthread_mutex_t mtx;
pthread_cond_t cnd;
int counter = 0;
pthread_t tid[NUM_OF_THREADS];

void* tWrite(void* arg){
    while(1){
        pthread_mutex_lock(&mtx);
		counter++;
		if(counter > 1)
			pthread_cond_wait(&cnd,&mtx);   
        sprintf(buf,"%d",counter);
        strcat(data,buf);
		sleep(rand()%3+1);
        pthread_mutex_unlock(&mtx);
    }
}

void* tRead(void* arg){
    sleep(1);
    while(1){
        pthread_mutex_lock(&mtx);
        rdCounter++;
        if(rdCounter >= NUM_OF_READERS){
            pthread_cond_broadcast(&cnd);
            rdCounter = 0;
        }
        printf("tid of reading thread = %lx data from writing thread =%s\n",(long)pthread_self(),data);
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
}

int main(int argc,char* argv[]){
    srand(time(NULL));
    data = (char*)malloc(150);
    if(pthread_mutex_init(&mtx,NULL) != 0){
        perror("rwlock init");
        exit(-1);
    }
    if(pthread_cond_init(&cnd,NULL) != 0){
        perror("cond init");
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
    pthread_mutex_destroy(&mtx);
    return 0;
}



