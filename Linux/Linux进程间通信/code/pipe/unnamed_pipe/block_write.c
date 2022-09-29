#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd[2];
	int ret;
	int i = 0;
	char write_buffer[] = "hello Linux!";

	ret = pipe(fd);
	if (ret < 0)
	{
		printf("create pipe failure\n");
		return -1;
	}
	printf("create pipe success fd[0]=%d, fd[2]=%d\n", fd[0], fd[1]);

	while (++i < 5500)
	{
		printf("%zu Bytes have been writen into pipe \n", sizeof(write_buffer) * i);
		write(fd[1], write_buffer, sizeof(write_buffer));
	}

	printf("write end\n");

	close(fd[0]);
	close(fd[1]);
	return 0;
}
