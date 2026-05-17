/* Problem Statement: Demonstration of pthread conditional variable  signal vs broadcast using mutex to protect the condition variable and ensure proper synchronization between threads. 
*The program creates multiple waiter threads that wait on a condition variable until they are signaled or broadcasted to proceed. 
*The main thread will signal one waiter and then broadcast to all waiters, showing the difference in behavior between the two methods.*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
int num = 1;
int thread_id = 1;

void* Thread_func(void* arg){
    int id = (int) *(int *)arg;
    while(num <= 12) {
    pthread_mutex_lock(&mutex);
        
        if (id != thread_id) 
        {
           if (id == 1)
            {
               printf("Thread1 waiting on condition variable: %d\n",id);
               pthread_cond_wait(&cond1, &mutex);
            }
            else if (id == 2)
            {
               printf("Thread2 waiting on condition variable:  %d\t%d\n",id,num);
               pthread_cond_wait(&cond2, &mutex);

            }
            else if (id == 3)
            {
                printf("Thread3 waiting on condition variable: %d\n%d",id,num);
                pthread_cond_wait(&cond3, &mutex);

            }
        }
      
        if(thread_id == 1)
        {
            printf("Thread%d: %d\n",id,num++);
            thread_id=2;
            pthread_cond_signal(&cond2);
            
        }
        else if (thread_id == 2)
        {
            printf("Thread%d: %d\n",id,num++);
            thread_id=3;
            pthread_cond_signal(&cond3);
            
        }
        else if (thread_id == 3)
        {
            printf("Thread%d: %d\n",id,num++);
            thread_id=1;
            pthread_cond_signal(&cond1);   
        }
         
        pthread_mutex_unlock(&mutex);
    }
   
}


int main(){
    pthread_t t[3];
    int i;
    for(i=1;i<4;++i)
    {
        pthread_create(&t[i],NULL,Thread_func,(void *)&i);
        sleep(1);
    }
    
    for(i=1;i<4;++i)
        pthread_join(t[i],NULL);
    
    return 0;
}


