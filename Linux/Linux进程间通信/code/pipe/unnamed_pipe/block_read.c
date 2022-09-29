#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd[2];
	int ret;
	char write_buffer[] = "hello world!";
	char read_buffer[128];

	ret = pipe(fd);
	if (ret < 0)
	{
		printf("create pipe failure\n");
		return -1;
	}
	printf("create pipe success fd[0]=%d, fd[2]=%d\n", fd[0], fd[1]);

	// write
	write(fd[1], write_buffer, sizeof(write_buffer));
	// read
	read(fd[0], read_buffer, sizeof(read_buffer));
	printf("read_buffer=%s\n", read_buffer);

	memset(read_buffer, 0, sizeof(read_buffer));

	// second read from pipe: block read
	read(fd[0], read_buffer, sizeof(read_buffer));
	printf("second read from pipe file\n");

	close(fd[0]);
	close(fd[1]);
	return 0;
}
