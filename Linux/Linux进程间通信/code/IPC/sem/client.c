#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// defined in <sys/types.h>
union semun
{
	int     val;            /* value for SETVAL */
	struct  semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
	u_short *array;         /* array for GETALL & SETALL */
};

int semid;					// ID of semaphrone set
union semun mysemun;		// union to help `semctl` to modify semaphrone set
struct sembuf mysembuf;		// struct to initialize semaphrone set

// main thread code
int main()
{
	int i, key;

	// create key for semaphrone set
	key = ftok("./sem.txt", 'a');
	if (key < 0)
	{
		perror("create key failed\n");
		return 1;
	}
	printf("create key success, key = %d\n", key);

	// create semaphrone set
	// the size of set is 3
	semid = semget(key, 3, IPC_CREAT | 0777);
	if (semid < 0)
	{
		perror("semget() failed");
		return 1;
	}

	// initialize sembuf
	mysembuf.sem_num = 0;	// set the index of semaphrone
	mysembuf.sem_flg = 0;	// 设置模式为阻塞模式

	// P
	mysembuf.sem_op = -1;
	semop(semid, &mysembuf, 1);
	for (i = 0; i < 10; i++)
	{
		usleep(100);
		printf("this is main function i = %d\n", i);
	}

	semctl(semid, 0, IPC_RMID);

	return 0;
}
