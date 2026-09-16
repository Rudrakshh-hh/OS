#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;
sem_t rw_mutex;

int readers=0,data=0;

void* reader(void* arg){
    sem_wait(&mutex);
    readers++;
    if(readers==1)sem_wait(&rw_mutex);

    sem_post(&mutex);
    printf("Reader is reading data: %d\n",data);
    
    sem_wait(&mutex);
    readers--;
    if(readers==0)sem_post(&rw_mutex);
    sem_post(&mutex);

    return NULL;
}
void* writer(void* arg){
    sem_wait(&rw_mutex);
    data++;
    printf("Writer is Writing data: %d\n",data);
    sem_post(&rw_mutex);

    return NULL;
}

void main(){
    sem_init(&mutex,0,1);
    sem_init(&rw_mutex,0,1);
    pthread_t r1,r2,w1;
    pthread_create(&r1,NULL,reader,NULL);
    pthread_create(&r2,NULL,reader,NULL);
    pthread_create(&w1,NULL,writer,NULL);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
}
