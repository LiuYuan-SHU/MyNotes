#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int msgid = msgget(IPC_PRIVATE, 0777);

	if (msgid < 0)
	{
		printf("create message queue failed\n");
		return -1;
	}
	printf("create message queue successfule with msgid = %d\n", msgid);

	system("ipcs -q");

	return 0;
}
