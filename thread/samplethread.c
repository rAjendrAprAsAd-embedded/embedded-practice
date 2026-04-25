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
	void *resp1,*resp2;
	int ret = pthread_create(&t1,NULL,Samplethread,NULL);
	printf("ret === %d\n",ret);

	int ret2=pthread_create(&t2,NULL,Samplethread2,NULL);
	printf("ret2 === %d\n",ret2);

	printf(" going to wait on pthreaad_join\n\n");
	int res1 = pthread_join(t1,&resp1);
	int res2 = pthread_join(t2,&resp2);
	printf("res1 =%d\t,res2= %d\n\n",res1,res2);
	printf("resp1=%s\nresp2=%s\n\n",(char *) resp1,(char *) resp2);
	printf(" Main program is going to end\n");
	return ;
}
