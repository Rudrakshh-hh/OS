#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>
#define SIZE 5

int buffer[SIZE];
int in=0,out=0;

sem_t empty,full,mutex;

void* producer(void* arg){

    for(int i=1;i<=10;i++){
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in]=i;
        printf("Produced: %d\n",i);
        in=(in+1)%SIZE;

        sem_post(&mutex);
        sem_post(&full);
    }

    return NULL;
}
void* consumer(void* arg){
    for(int i=1;i<=10;i++){
        sem_wait(&full);
        sem_wait(&mutex);

        int item=buffer[out];
        printf("Consumed: %d\n",item);
        out=(out+1)%SIZE;

        sem_post(&mutex);
        sem_post(&empty);
    }

    return NULL;
}

void main(){
    sem_init(&empty,0,SIZE);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);

    pthread_t prod,cons;

    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
}