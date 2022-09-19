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
	// 定义监听Socket
	// 定义连接客户端的socket
	int serv_sock, clnt_sock;
	// 定义存储客户端发来消息的buffer
	char message[BUF_SIZE];
	// 记录发来消息的长度
	// 迭代次数
	int str_len, i;

	// 记录服务端、客户端协议族、地址族和端口号
	struct sockaddr_in serv_adr, clnt_adr;
	// 记录客户端地址长度
	socklen_t clnt_adr_sz;

	// 程序参数判断
	if (argc != 2)
	{
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}

	// 设置监听Socket：使用IPv4，流式传输
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1) 
	{
		error_handling("socket() error");
	}

	// 设置客户端sockaddr_in结构体
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	// 绑定服务端地址信息与socket
	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
	{
		error_handling("bind() error");
	}

	// 设置为监听模式
	if (listen(serv_sock, 5) == -1)
	{
		error_handling("listen() error");
	}

	// 记录客户端地址结构体大小
	clnt_adr_sz = sizeof(clnt_adr);

	// 接收5次请求后结束
	for (i = 0; i < 5; i++)
	{
		// 处理请求
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		if (clnt_sock == -1)
		{
			error_handling("accept() error");
		}
		else
		{
			printf("Connected client %d \n", clnt_sock);
		}

		// 回声
		while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
		{
			write(clnt_sock, message, str_len);
		}

		close(clnt_sock);
	}

	close(serv_sock);

	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
