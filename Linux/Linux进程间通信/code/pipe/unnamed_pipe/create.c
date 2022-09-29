#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd[2];
	int ret;

	ret = pipe(fd);
	if (ret < 0)
	{
		printf("create pipe failure\n");
		return -1;
	}
	printf("create pipe success fd[0]=%d, fd[2]=%d", fd[0], fd[1]);

	return 0;
}
