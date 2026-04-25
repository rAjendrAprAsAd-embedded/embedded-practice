/*
 *pthread_join terminates immediately and it will also have the threaad1 return value.
 *
 * */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h> // for sleep()
void * Samplethread2()
{
 printf("hey bossy i'm in Samplethread2 thread\n\n");
 return "Samplethread2";

}

void * Samplethread()
{
   printf("hey boss i'm in samplethread\n\n");
   sleep(5);
   printf("samplethread terminating\n");
   return "Samplethread";
}

void main()
{

	pthread_t t1,t2;
	void *resp1,*resp2;
	int ret = pthread_create(&t1,NULL,Samplethread,NULL);
	printf("ret === %d\n",ret);

	int ret2=pthread_create(&t2,NULL,Samplethread2,NULL);
	printf("ret2 === %d\n",ret2);

	int cancel_ret = pthread_cancel(t1);
	if (cancel_ret != 0)
	    printf("pthread_cancel ret is = %d",cancel_ret);

	printf(" going to wait on pthreaad_join\n\n");
	int res1 = pthread_join(t1,&resp1);//as thread1 cancelled resp1 will have the -1,if we print direcly using %s it cause Segmentation fault
	if (resp1 == PTHREAD_CANCELED)
	    printf("main(): thread was canceled thread1 & res = %d\n",res1);
        else
	{
	    printf("return value of thread_join t1 i.e.res1 = %d\n",res1);
	    printf("resp1=%s\n",(char *) resp1);
	}
	sleep(1); // wait until thread2 exit
	int cancel_ret2 = pthread_cancel(t2);
        if (cancel_ret2 != 0)
        {
            printf("pthread_cancel ret is = %d",cancel_ret2);
        }
	
	int res2 = pthread_join(t2,&resp2);
        if (resp2 == PTHREAD_CANCELED)
            printf("main(): thread was canceled thread2 & res = %d\n",res2);
        else
	{	
            printf("return value of thread_join t2 i.e.res2 = %d\n",res2);
	    printf("resp2=%s\n",(char *) resp2);
	}
	printf(" Main program is going to end\n");
	return ;
}
