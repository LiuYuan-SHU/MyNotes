#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char process_inter = 0;
	int fd = open("./myfifo", O_WRONLY);
	if (fd < 0)
	{
		printf("open myfifo failure\n");
		return -1;
	}
	printf("open myfifo success");

	int i = 0;
	for (; i < 5; i++)
	{
		printf("this is first process i = %d\n", i);
		usleep(100);
	}
	sleep(5);
	process_inter = 1;
	write(fd, &process_inter, sizeof(process_inter));

	while (1) {}
	return 0;
}
