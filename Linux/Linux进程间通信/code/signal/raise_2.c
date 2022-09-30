#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	pid_t pid = fork();
	if (pid == 0)
	{
		printf("child process raise function before\n");
		raise(SIGTSTP);
		printf("child process raise function after\n");
	}
	else
	{
		sleep(8);
		if (waitpid(pid, NULL, WNOHANG) == 0)
		{ kill(pid, 9); }
		while (1) {}
	}
}
