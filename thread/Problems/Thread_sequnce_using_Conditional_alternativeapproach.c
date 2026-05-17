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

void* Thread_func1(void* arg){

    while(num <= 12) {

    pthread_mutex_lock(&mutex);

    printf("Thread_func1 waiting on condition variable = %d\n",100+num++);
    pthread_cond_signal(&cond2);
    sleep(1);
    pthread_cond_wait(&cond1, &mutex);
    pthread_mutex_unlock(&mutex);
    }
}

void* Thread_func2(void* arg){

    while(num <= 12) {

    pthread_mutex_lock(&mutex);
    printf("Thread_func2 waiting on condition variable = %d\n",200+num++);
    pthread_cond_signal(&cond3);
    sleep(1);
    pthread_cond_wait(&cond2, &mutex);
    pthread_mutex_unlock(&mutex);
    }
}
void* Thread_func3(void* arg){

    while(num <= 12) {

    pthread_mutex_lock(&mutex);
    printf("Thread_func3 waiting on condition variable = %d\n",300+num++);
    if(num >= 12) 
    { 
        //can you write the code terminate all the thread once it reaches 12, so that they don't get stuck waiting on the condition variable? 
        pthread_cond_signal(&cond1);
        pthread_cond_signal(&cond2);
        pthread_cond_signal(&cond3);
        pthread_mutex_unlock(&mutex);
        break;
    }

        
    pthread_cond_signal(&cond1);
    sleep(1);
    pthread_cond_wait(&cond3, &mutex);
    pthread_mutex_unlock(&mutex);
    }
}

int main(){
    pthread_t t1,t2,t3;
    int i=1;
    
    pthread_create(&t1,NULL,Thread_func1,(void *)&i);
    pthread_create(&t2,NULL,Thread_func2,(void *)&i);
    pthread_create(&t3,NULL,Thread_func3,(void *)&i);
    sleep(1);
    
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    printf("All threads completed.\n");

    return 0;
}


