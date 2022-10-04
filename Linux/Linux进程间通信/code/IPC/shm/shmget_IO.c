#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int shmid;
	shmid = shmget(IPC_PRIVATE, 128, IPC_CREAT | 0777);

	if (shmid < 0)
	{
		printf("create shared memory failed\n");
		return 1;
	}
	else 
	{
		printf("create shared memory sucess shmid=%d\n", shmid);	
	}

	char* p = (char*)shmat(shmid, NULL, 0);
	if (!p)
	{
		printf("shmat map failed\n");
		return 1;
	}
	// write shm
	fputs("input data: ", stdout);
	fgets(p, 128, stdin);

	// read shm
	printf("shared memory data:%s\n", p);
	printf("shared memory data second time:%s", p);

	// delete IPC
	char buffer[128];
	sprintf(buffer, "ipcrm -m %d", shmid);
	system(buffer);

	return 0;
}
