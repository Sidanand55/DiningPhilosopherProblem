// using sauce bottles and semaphores

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5

sem_t room;
sem_t sauce[2];
sem_t chop[5];

void eat(int phil){
    printf("Philosopher %d is eating with %d sauce\n", phil,phil&2);
}

void *philosopher(void* num){
    int phil =*(int*) num;
    
    sem_wait(&room);
    printf("Philosopher %d has entered room \n",phil);
    sem_wait(&sauce[phil%2]);
    sem_wait(&chop[(phil+1)%5]);
    sem_wait(&chop[phil]);

    eat(phil);
    // sleep(2);

   
    printf("Philosopher %d has finished eating\n",phil);

    sem_post(&chop[phil]);
    sem_post(&chop[(phil+1)%5]);
    sem_post(&sauce[phil%2]);
    sem_post(&room);
    
}


int main(){

    pthread_t thread_id[N];
    int a[N];

    sem_init(&chop[0],0,1);
    sem_init(&chop[1],0,1);
    sem_init(&chop[2],0,1);
    sem_init(&chop[3],0,1);
    sem_init(&chop[4],0,1);
    sem_init(&room,0,4);
    sem_init(&sauce[0],0,1);
    sem_init(&sauce[1],0,1);

    for(int i=0;i<N;i++){

        pthread_create(&thread_id[i],NULL,philosopher,&i);

    }

    for (int i = 0; i < N; i++)
    {
         pthread_join(thread_id[i],NULL);
    }



}

