# 回声客户端的完美实现

## 回声服务端没有问题，只有回声客户端有问题？

问题不在服务器端，而在服务端。下面是[`echo_server.c`](../示例代码/echo_server.c)的相应代码：

```c
// 回声
while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
{
	write(clnt_sock, message, str_len);
}
```
再来看[`echo_client.c`](../示例代码/echo_client.c)的代码：

```c
write(sock, message, strlen(message));
str_len = read(sock, message, BUF_SIZE - 1);
```

两边都调用了`read`和`write`函数，但之所以只有客户端有问题，是因为：

+ 我们所有的数据都是通过`write`函数一次性发送的
+ 之后立刻调用一次`read`函数，期待着接收自己传输的字符串

的确，在我们发送数据之后，我们确实就可以接收数据。但是需要等多久？这并不符合常理。

## 回声客户端问题解决方法

回声客户端所存在的问题其实是初级程序员经常犯的错误，其实对于本程序来说，这个问题很好解决。因为我们可以提前确定接受数据的大小：

```c
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
```
## 如果问题不在于回声客户端：定义应用协议

回声客户端可以提前知道接收的数据长度，但我们应该意识到，更多情况下这不太可能。既然如此，若无法预知接收数据长度时应该如何收发数据？此时需要的就是应用层协议的定义。

我们之前的协议是：

> ###### 收到Q就立即终止连接

同样，收发数据过程中也需要定好规则（协议）以表示数据的边界，或提前告知收发数据的大小。服务器端/客户端实现过程中逐步定义的这些规则就是应用层协议。可以看出，***应用层协议并不是高深莫测的存在，只不过是为特定程序的实现而制定的规则。***

## 编写自己的计算机程序

# TCP原理
