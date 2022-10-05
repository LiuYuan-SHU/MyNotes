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

// child thread code
void * func(void * var)
{
	int j;

	mysembuf.sem_op = -1;
	// P: wait
	// operate on semaphrone set specified by `semid`
	// the content of operation is specified by the struct `mysembuf`
	// the number of semaphrones to be operated on is `1`
	semop(semid, &mysembuf, 1);
	for (j = 0; j < 10; j++)
	{
		usleep(100);
		printf("this is fun j = %d\n", j);
	}

	return NULL;
}

// main thread code
int main()
{
	int i;
	char str[] = "hello Linux\n";
	pthread_t tid;

	// create semaphrone set
	// the size of set is 3
	semid = semget(IPC_PRIVATE, 3, 0777);
	if (semid < 0)
	{
		perror("semget() failed");
		return 1;
	}

	// initialize senum
	// set the value of semaphrones in semaphrone set as 0
	mysemun.val = 0;
	// initialize semaphrone
	// set the #0 semaphrone's value as 0
	semctl(semid, 0, SETVAL, mysemun);

	// initialize sembuf
	mysembuf.sem_num = 0;	// set the index of semaphrone
	mysembuf.sem_flg = 0;	// 设置模式为阻塞模式
	
	// create thread
	if (pthread_create(&tid, NULL, func, (void*)str) < 0)
	{
		perror("create child thread failed\n");
		return 1;
	}

	for (i = 0; i < 10; i++)
	{
		usleep(100);
		printf("this is main function i = %d\n", i);
	}
	// V
	mysembuf.sem_op = 1;
	semop(semid, &mysembuf, 1);

	pthread_join(tid, NULL);

	semctl(semid, 0, IPC_RMID);

	return 0;
}
