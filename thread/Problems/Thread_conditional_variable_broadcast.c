/* Problem Statement: Demonstration of pthread conditional variable  signal vs broadcast using mutex to protect the condition variable and ensure proper synchronization between threads. 
*The program creates multiple waiter threads that wait on a condition variable until they are signaled or broadcasted to proceed. 
*The main thread will signal one waiter and then broadcast to all waiters, showing the difference in behavior between the two methods.*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int ready = 0;

void* waiter(void* arg){
    int id = (int)(long)arg;
    pthread_mutex_lock(&mutex);
    while (!ready) 
    {
        pthread_cond_wait(&cond, &mutex);// it releases mutex and waits, when signaled it re-acquires mutex before returning
    }
    printf("Waiter %d proceeding\n", id); 
    /*once signaled, it will print and exit, if pthread_mutex_unlock is not there, only one waiter will proceed,
     the rest will be stuck waiting for the mutex to be released, even if they were signaled by broadcast, 
    because they can't acquire the mutex to check the condition and proceed.*/
    pthread_mutex_unlock(&mutex);


    return NULL;
}

int main(){
    const int N=10; pthread_t t[N];
    for (long i=0;i<N;++i) 
    {
        pthread_create(&t[i],NULL,waiter,(void*)i);
    }
    sleep(1);

    // signal: wake one thread, but we don't know which one will be woken up, and the rest will still be waiting

   /* pthread_mutex_lock(&mutex); 
    printf("Signaling one waiter...\n");
    ready=1; 
    pthread_cond_signal(&cond); 
    pthread_mutex_unlock(&mutex);
    */
    
    sleep(1);
    // reset and broadcast
    pthread_mutex_lock(&mutex); 
    ready=1; 
    pthread_cond_broadcast(&cond); 
    /* wake all waiters, but they will still need to acquire the mutex one by one but not in the sequencehe condition and proceed, 
     because they can't acquire the mutex to check the condition and proceed.*/
    pthread_mutex_unlock(&mutex);
    

    for (int i=0;i<N;++i) 
    {
        pthread_join(t[i],NULL);
    }
    return 0;
}
