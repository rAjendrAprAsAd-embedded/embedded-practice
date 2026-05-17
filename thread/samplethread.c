/*
 *pthread_join terminates immediately and it will also have the threaad1 return value.
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int long counter = 0;

void * Samplethread2(void* arg)
{
	int times = *((int*)arg);
 	printf("hey bossy i'm in Samplethread2 thread\n\n");
 	for (int i=0;i<times;++i){
    	pthread_mutex_lock(&lock);
 		printf("hey bossy i'm in Samplethread2 thread\n\n");
        counter++;
        pthread_mutex_unlock(&lock);
    }
 return "Samplethread2";
}

void * Samplethread(void* arg)
{
    int times = *((int*)arg);
	for (int i=0;i<times;++i){
    	pthread_mutex_lock(&lock);
	  	printf("hey boss i'm in samplethread\n\n");
        counter++;
        pthread_mutex_unlock(&lock);
    }
   printf("samplethread terminating\n\n\n");
   return "Samplethread";
}

void main()
{

	pthread_t t1,t2;
	 const int times = 50000;
	void *resp1,*resp2;
	int ret = pthread_create(&t1,NULL,Samplethread,(void*)&times);
	printf("ret === %d\n",ret);
	int ret2=pthread_create(&t2,NULL,Samplethread2,(void*)&times);
	printf("ret2 === %d\n",ret2);
	printf(" going to wait on pthreaad_join\n\n");
	int res1 = pthread_join(t1,&resp1);
	int res2 = pthread_join(t2,&resp2);
	printf("res1 =%d\t,res2= %d\n\n",res1,res2);
	if (resp1 != PTHREAD_CANCELED && resp2 != PTHREAD_CANCELED)//if thread not cancelled then only typecase can work else gives segmentation fault
	{
	    printf("resp1=%s\nresp2=%s\n\n",(char *) resp1,(char *) resp2);
	}
	printf("Final counter=%ld (expected %d)\n", counter, times*2);
	/*
	witout mutex output is Final counter=82279 (expected 100000)
	*/
	printf(" Main program is going to end\n");
	return ;
}
