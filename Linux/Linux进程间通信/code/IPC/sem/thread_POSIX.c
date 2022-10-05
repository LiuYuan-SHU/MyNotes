#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

// child thread code
void * func(void * var)
{
	int j;

	// P: wait
	sem_wait(&sem);
	for (j = 0; j < 10; j++)
	{
		usleep(100);
		printf("this is fun j = %d\n", j);
	}
	// V: finished
	sem_post(&sem);

	return NULL;
}

// main thread code
int main()
{
	int i;
	char str[] = "hello Linux\n";
	pthread_t tid;

	// initialize semaphore
	sem_init(&sem, 0, 0);	

	if (pthread_create(&tid, NULL, func, (void*)str) < 0)
	{
		perror("create thread failed\n");
		return 1;
	}

	for (i = 0; i < 10; i++)
	{
		usleep(100);
		printf("this is main function i = %d\n", i);
	}
	// V: finished
	sem_post(&sem);

	pthread_join(tid, NULL);

	return 0;
}
