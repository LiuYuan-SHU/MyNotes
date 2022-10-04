#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int shmid;
	int key;

#ifndef _FTOK
	key = IPC_PRIVATE;
#else
	key = ftok("./shm.txt", 'a');
#endif
	// 如果是使用ftok返回的key值，读写权限一定需要与IPC_CREATE做按位与
	shmid = shmget(key, 128, IPC_CREAT | 0777);

	if (shmid < 0)
	{
		printf("create shared memory failed\n");
		return 1;
	}
	else 
	{
		printf("create shared memory sucess shmid=%d\n", shmid);	
	}

	// check IPC
	system("ipcs -m");
	// delete IPC
	char buffer[128];
	sprintf(buffer, "ipcrm -m %d", shmid);
	system(buffer);

	return 0;
}
