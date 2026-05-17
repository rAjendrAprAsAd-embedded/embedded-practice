/* ProblemStatement 2: Create threads that compute partial sums. Each thread calculates sum of array elements in its assigned range and returns the result. 
Main thread collects and prints total sum.*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct range {int start, end; };//to calculte sum b/w the given range

void* Thread_sum(void* arg) {
    struct range *r = arg;
    long *res = malloc(sizeof(long));
    for (int i = r->start; i < r->end; ++i) 
    {
        *res += i;
    }
    return res;
}

int main(void) {
    const int N = 1000;
    pthread_t tid[4]; //4threads 
    struct range ranges[4];//4 ranges one for each
    
    ranges[0].start = 0;
    ranges[0].end = 250;
    ranges[1].start=ranges[0].end;
    ranges[1].end=500;
    ranges[2].start=ranges[1].end;
    ranges[2].end=750;
    ranges[3].start=ranges[2].end;
    ranges[3].end=1001;

    for(int i=0;i<4;i++)
        pthread_create(&tid[i], NULL, Thread_sum, &ranges[i]);

    long SumofThread = 0;
    void *resp;
    for (int i=0;i<4;++i) {
        pthread_join(tid[i], &resp);
       // printf("=====ret value from tid[%d] is %d\n",i+1,*(int*)resp);
        SumofThread += *(int*)resp;
	free(resp);
    }
    printf("Total sum = %ld (expected %d)\n", SumofThread, N);
    return 0;
}
