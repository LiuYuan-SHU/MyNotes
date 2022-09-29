#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid;
	int process_inter = 0;
	int pipe_fd[2];
	int ret;
	
	if ((ret = pipe(pipe_fd)) == -1) { perror("pipe() error"); }

	if ((pid = fork()) < 0) { perror("fork() error"); }
	else if (pid == 0)
	{
		int i = 0;
		// if pipe is empty, sleep
		read(pipe_fd[0], &process_inter, sizeof(process_inter));
		while (process_inter == 0) {}
		
		for ( ; i < 5; i++ )
		{
			printf("this is child process i = %d\n", i);
		}
	}
	else
	{
		int i = 0;
		for (; i < 5; i++)
		{
			printf("this is parent process i = %d\n", i);
			usleep(100);
		}
		process_inter = 1;
		write(pipe_fd[1], &process_inter, sizeof(process_inter));
	}
}
