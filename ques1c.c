// only sema phores and threads
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5

sem_t room;
// counting semaphore for checking the number of people at table at a time. 
sem_t chop[5];
 // 5 forks acting as semaphores,each acts as a binary semaphores

void eat(int phil){
    printf("Philosopher %d is eating\n", phil);
}

void *philosopher(void* num){
    int phil =*(int*) num;

    sem_wait(&room);
    printf("Professor %d has entered the room\n",phil);

    sem_wait(&chop[phil]);
    sem_wait(&chop[(phil+1)%5]);

    eat(phil);
    sleep(2);
    printf("\nPhilosopher %d has finished eating\n", phil);

    sem_post(&chop[(phil+1)%N]);
    sem_post(&chop[phil]);
    sem_post(&room);

}


int main(){

    int a[N];
    pthread_t thread_id[N];

    sem_init(&room,0,4);

    for(int i=0;i<N;i++){
        sem_init(&chop[i],0,1);
    }

    for(int i=0;i<N;i++){
        a[i]=i;
        pthread_create(&thread_id[i],NULL,philosopher, &a[i]);
    }

    for(int i =0;i<N;i++){
        pthread_join(thread_id[i],NULL);
    }

}


