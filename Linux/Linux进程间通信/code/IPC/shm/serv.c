#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct data
{
	pid_t pid;
	char buffer[128];
};

void myfunc(int sig) { return; }

int main()
{
	int shmid, key;
	struct data* p;

	// preprare shared memory
	key = ftok("./shm.txt", 'a');
	if (key < 0) { perror("ftok failed\n"); return 1; }
	shmid = shmget(key, 128, IPC_CREAT | 0777);
	if (shmid < 0)
	{
		printf("create shared memory failed\n");
		return 1;
	}
	printf("create shared memory finished\n");

	// add signal handler
	signal(SIGUSR2, myfunc);
	
	// prepare buffer
	p = (struct data*)shmat(shmid, NULL, 0);
	if (!p)
	{
		printf("shmat map failed\n");
		return 1;
	}

	// write server pid first
	printf("write pid %d to buffer\n", getpid());
	p->pid = getpid();
	// wait for client to read data
	pause();
	// read the pid of client
	pid_t client_pid = p->pid;	
	printf("accept signal from client\n");

	while (1) 
	{
		printf("parent process start write shared memory: ");
		// write data to shared memory
		fgets(p->buffer, 128, stdin);
		// tell client to read data
		kill(client_pid, SIGUSR1);
		// wait child to read
		pause();
	}

	return 0;
}
