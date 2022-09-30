#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[])
{
	assert(argc == 3);

	int sig, pid;
	sig = atoi(argv[1]);
	pid = atoi(argv[2]);

	kill(pid, sig);

	return 0;
}
