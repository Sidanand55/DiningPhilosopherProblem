// strict oredering
// only philosophers

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdint.h>

#define N 5

void eat(int phil){
  
  printf("Philosopher %d is eating\n", phil);

}
int phil = 2;
int fork_phil = 5;

void reassign(){
    phil++;
    fork_phil++;
    fork_phil++;
}

void *philosopher(void* num){
    int p =*(int*) num;  

    if(phil> 0){
        if(fork_phil > 1){
            phil--;
            fork_phil--;
            fork_phil--;
            // printf("Philospher %d is running with forks\n", phil);
        }
    }
    else{
        for(;;){
            if(phil > 0 ){
                phil--;
                fork_phil--;
                fork_phil--;
                // printf("Philospher %d is running with forks \n", phil);
                break;
            }
            else if(fork_phil > 1){
                phil--;
                fork_phil--;
                fork_phil--;
                // printf("Philospher %d is running with forks \n", phil);
                break;
            }
            else if(phil > 0 && fork_phil > 1){
                phil--;
                fork_phil--;
                fork_phil--;
                // printf("Philospher %d is running with forks\n", phil);
                break;
            }
        }
    }
    
    eat(p);
    printf("\nPhilosopher %d has finished eating\n", p);

    reassign();

}


int main(){

  pthread_t thread_id[N];

  for(int i=0;i<N;i++){
    pthread_create(&thread_id[i], NULL, &philosopher,&i);
    pthread_join(thread_id[i],NULL);
  }

//   for(int i=0;i<5;i++){
//     pthread_join(thread_id[i],NULL);
//   }
 
}
