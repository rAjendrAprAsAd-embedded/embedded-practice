#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void sigHandler(int sig)
{	static int cnt = 0;
	printf("Signal INT rcvd!\n");
	if(sig == SIGINT)
	{	
		cnt++;
		printf("hey boss SIGINT rcvd %d \n",cnt);
		return ;
	}
	
	if (cnt > 10)
	{
		printf("hey boss SIGQUIT rcvd and killing \n");
		exit(EXIT_SUCCESS);
	}
	if(sig == SIGKILL)
        {
                cnt++;
                printf("hey boss SIGkill rcvd %d \n",cnt);
                return ;
        }
	printf("hey boss SIGQUIT rcvd \n");
	
}


int main(int argc, char *argv[])
{

    int j;
    if (signal(SIGINT, sigHandler) == SIG_ERR)
	printf("signal registration failed");
 
    if (signal(SIGQUIT, sigHandler) == SIG_ERR)
        printf("signal registration failed");
    /*
     * Forcefully kills the process immediately via the kernel.
     * it can't be caught.
     */
    if (signal(SIGKILL, sigHandler) == SIG_ERR)
        printf("signal registration failed");

    for (j = 0; ; j++) {
	printf("Instruction %d executing \n", j);
	sleep(3);
    }
}
