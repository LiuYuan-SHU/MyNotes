#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	int i = 0;

	printf("pause before\n");
	pause();
	printf("pause after\n");

	// 为了让程序能够等到内核发送信号给它
	while (i < 20) 
	{
		i++;
		sleep(1);
		printf("process things, i = %d\n", i);
	}

	return 0;
}
