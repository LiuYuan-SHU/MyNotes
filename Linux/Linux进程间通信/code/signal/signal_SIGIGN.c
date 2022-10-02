#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void my_func(int signum);

int main()
{
	int i = 0;

	signal(SIGALRM, my_func);
	printf("alarm before\n");
	alarm(9);	
	printf("alarm after\n");
	// 覆盖原来声明的处理方法
	signal(SIGALRM, SIG_IGN);

	// 为了让程序能够等到内核发送信号给它
	while (i < 10) 
	{
		i++;
		sleep(1);
		printf("process things, i = %d\n", i);
	}

	return 0;
}

void my_func(int signum)
{
	int i = 0;
	while (i < 10)
	{
		printf("process signal signum=%d\n", i++);
		sleep(1);
	}

	return;
}
