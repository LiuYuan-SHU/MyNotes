#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void myfunc(int sig) { return; }

int main()
{
	int shmid;
	char* p;
	shmid = shmget(IPC_PRIVATE, 128, IPC_CREAT | 0777);

	if (shmid < 0)
	{
		printf("create shared memory failed\n");
		return 1;
	}
	printf("create shared memory finished\n");

	pid_t pid = fork();

	// parent process
	if (pid > 0)
	{
		// add signal handler
		signal(SIGUSR2, myfunc);
		
		p = (char*)shmat(shmid, NULL, 0);
		if (!p)
		{
			printf("shmat map failed\n");
			return 1;
		}

		while (1) 
		{
			printf("parent process start write shared memory: ");
			// write data to shared memory
			fgets(p, 128, stdin);
			// tell child to read data
			kill(pid, SIGUSR1);
			// wait child to read
			pause();
		}
	}
	// child process
	else
	{
		signal(SIGUSR1, myfunc);
		
		p = (char*)shmat(shmid, NULL, 0);
		if (!p)
		{
			printf("shmat map failed\n");
			return 1;
		}

		while (1)
		{
			// wait parent to write	
			pause();
			printf("shared memory data:%s", p);
			kill(getppid(), SIGUSR2);
		}
	}

	return 0;
}
