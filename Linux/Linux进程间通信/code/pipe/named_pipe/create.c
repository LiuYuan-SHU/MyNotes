#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int ret;
	ret = mkfifo("./myfifo", 07777);
	if (ret < 0)
	{
		printf("create myfifo failure");
		return -1;
	}

	printf("create myfifo success");

	return 0;
}
