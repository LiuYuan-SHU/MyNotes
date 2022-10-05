#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int semid = semget(IPC_PRIVATE, 3, 0777);

	if (semid < 0)
	{
		printf("create semaphore failed\n");
		return -1;
	}
	printf("create semaphore successfule with msgid = %d\n", semid);

	char buffer[128];
	sprintf(buffer, "ipcs -s | grep %d", semid);
	system(buffer);

	return 0;
}
