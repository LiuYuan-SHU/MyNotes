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
	int shmid;
	struct data* p;

	// prepare shared memor
	int key = ftok("./shm.txt", 'a');
	shmid = shmget(key, 128, IPC_CREAT | 0777);
	if (shmid < 0)
	{
		printf("create shared memory failed\n");
		return 1;
	}
	printf("create shared memory finished\n");

	signal(SIGUSR1, myfunc);
	
	p = (struct data*)shmat(shmid, NULL, 0);
	if (!p)
	{
		printf("shmat map failed\n");
		return 1;
	}

	// read the pid of server
	pid_t server_pid = p->pid;
	printf("read server pid: %d\n", server_pid);
	printf("write client pid: %d\n", getpid());
	// tell server the pid of client
	p->pid = getpid();
	kill(server_pid, SIGUSR2);

	while (1)
	{
		// wait parent to write	
		pause();
		printf("shared memory data:%s", p->buffer); 
		kill(server_pid, SIGUSR2);
	}

	return 0;
}
