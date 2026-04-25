/*
 *pthread_join terminates immediately and it will also have the threaad1 return value.
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void * Samplethread2()
{
 printf("hey bossy i'm in Samplethread2 thread\n\n");
 return "Samplethread2";

}



void * Samplethread()
{
   printf("hey boss i'm in samplethread\n\n");
   printf("samplethread terminating\n\n\n");
   return "Samplethread";
}

void main()
{

	pthread_t t1,t2;
	void *resp;
	int ret = pthread_create(&t1,NULL,Samplethread,NULL);
	printf("ret === %d\n",ret);
	
	int ret2=pthread_create(&t2,NULL,Samplethread2,NULL);
	
	printf(" Main program is going to end\n");
	return ;
}
