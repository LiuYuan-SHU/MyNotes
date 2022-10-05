#include <stddef.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct msgbuf
{
	long mtype;
	char voltage[124];
	char ID[4];
};

int main()
{
	int msgid = msgget(IPC_PRIVATE, 0777);
	struct msgbuf send_buffer, recv_buffer;

	if (msgid < 0)
	{
		printf("create message queue failed\n");
		return -1;
	}
	printf("create message queue successfule with msgid = %d\n", msgid);

	system("ipcs -q");

	// write message
	// init buffer
	send_buffer.mtype = 100;
	printf("please input message: ");
	fgets(send_buffer.voltage, 124, stdin);
	// send message
	msgsnd(msgid, (void *)&send_buffer, strlen(send_buffer.voltage), 0);

	// read message
	memset(&recv_buffer, 0, sizeof(recv_buffer));	
	size_t read_len = msgrcv(msgid, (void *)&recv_buffer, 124, 100, 0);
	printf("read message of length %zu from message queue : %s\n", read_len, recv_buffer.voltage);

	// read again
	// memset(&recv_buffer, 0, sizeof(recv_buffer));	
	// read_len = msgrcv(msgid, (void *)&recv_buffer, 124, 100, 0);
	// printf("read message of length %zu from message queue : %s\n", read_len, recv_buffer.voltage);

	// delete msq
	msgctl(msgid, IPC_RMID, NULL);	

	return 0;
}
