#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char process_inter = 0;
	int fd = open("./myfifo", O_RDONLY);
	if (fd < 0)
	{
		printf("open myfifo failure\n");
		return -1;
	}
	printf("open myfifo success");

	process_inter = 1;
	read(fd, &process_inter, 1);

	int i = 0;
	for (; i < 5; i++)
	{
		printf("this is second process i = %d\n", i);
		usleep(100);
	}
	while (!process_inter) {}
	return 0;
}
