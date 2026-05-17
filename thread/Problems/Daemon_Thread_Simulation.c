/*
 *ProblemStatement 1: Implement a thread that periodically writes status updates while main thread continues other work. Main  can terminate the  the thread gracefully.
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
//shared variable between main and thread
int kill=1;

void * Samplethread()
{
   while(kill)
   {
        printf("hey boss i'm in samplethread\n\n");
	sleep(1);
   }
   printf("samplethread terminating\n\n\n");
   return "Samplethread";
}

void main()
{

	pthread_t t1,t2;
	void *resp1,*resp2;
	int ret = pthread_create(&t1,NULL,Samplethread,NULL);
	printf("ret === %d\n",ret);
	sleep(50);//do other activities here
	kill=0;
	//pthread_cancel(t1);
	printf(" going to wait on pthreaad_join\n\n");
	int res1 = pthread_join(t1,&resp1);
	if (resp1 != PTHREAD_CANCELED)//if thread not cancelled then only typecase can work else gives segmentation fault
	{
	    printf("resp1=%s\n\n",(char *) resp1);
	}
	printf(" Main program is going to end\n");
	return ;
}
