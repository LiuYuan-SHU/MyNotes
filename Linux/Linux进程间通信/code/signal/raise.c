#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	printf("raise before\n");
	raise(9);	// _exit()
	printf("after raise");

	return 0;
}
