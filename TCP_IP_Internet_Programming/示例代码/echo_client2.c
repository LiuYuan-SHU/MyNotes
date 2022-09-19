#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char* message);

int main(int argc, char* argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len, recv_len, revc_cnt;
	struct sockaddr_in serv_adr;

	if (argc != 3)
	{
		fprintf(stdout, "Usage : %s <IP> <port> \n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("sock() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error");
	else
		fputs("connected ......\n", stdout);
	
	while (1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		str_len = write(sock, message, strlen(message));

		recv_len = 0;
		// 当读取的字节数没有到达填写的长度时
		// 即使出现异常，导致读取了过多的字节，也会在大于的时候退出，比!= 更好用
		while (recv_len < str_len)
		{
			revc_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
			if (revc_cnt == -1)
			{
				error_handling("read() error");
			}

			recv_len += revc_cnt;
		}

		message[recv_len] = 0;
		fprintf(stdout, "Message from server: %s", message);
	}

	close(sock);

	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
