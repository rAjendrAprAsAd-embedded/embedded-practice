/* ProblemStatement : Implement thread pool with worker threads waiting on condition variable for work items until the producer enqueues tasks; 
 * workers waits until producer fills.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define WORKERS 4


typedef struct Node {
    int data; 
    struct Node *next; 
}list_t;

list_t *head = NULL; 
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t qcv = PTHREAD_COND_INITIALIZER;
int completed = 0;

void enqueue(list_t *t){ 
    pthread_mutex_lock(&qlock); 
    t->next = head; 
    head = t; 
    pthread_cond_signal(&qcv);
    pthread_mutex_unlock(&qlock); 
}

list_t* dequeue(int thread_id){
    list_t *t = NULL; 
    pthread_mutex_lock(&qlock); 
    
    while (!head && !completed) 
    {
        printf("Worker %d waiting until Node has added\n", thread_id);
        pthread_cond_wait(&qcv, &qlock); 
    }
    printf("Worker %d received a Node\n", thread_id);
    if (head){
        t=head;
        head=head->next; 
    }
    pthread_mutex_unlock(&qlock); 
    return t; 
}

void* worker(void* arg){ 
    int threadid_id = *(int*)arg;
    while (1){
        list_t *tmp= dequeue(threadid_id);
        if (!tmp){
            break;
        } 
        printf("Worker %d processing task %d\n", threadid_id, tmp->data); 
        usleep(100000); 
        free(tmp); 
    } 
    return NULL; 
}

int main(){ 
    pthread_t w[WORKERS]; 
    int x[4];
    for (int i=0;i<WORKERS;++i) 
    {   
        x[i] = i+1;
        pthread_create(&w[i],NULL,worker,&x[i]);
    }

    //creating 20 Nodes by producer
    for (int i=0;i<20;++i){ 
        list_t *tmp = malloc(sizeof(list_t)); 
        tmp->data = i; 
        enqueue(tmp); 
    }
    // shutdown main
    printf("Main thread signaling shutdown\n");
    pthread_mutex_lock(&qlock);
    completed=1; 
    pthread_mutex_unlock(&qlock);
    printf("Main thread waiting for workers to finish\n");

    for (int i=0;i<WORKERS;++i) pthread_join(w[i],NULL);

    return 0; 
}
