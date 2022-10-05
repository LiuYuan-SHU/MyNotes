#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

void * handle_clnt(void * arg);
void send_msg(char* msg, int len);
void error_handling(char * msg);

int clnt_cnt = 0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutex;

int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	pthread_t t_id;

	// parameter checking
	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		return 1;
	}

	// initialization
	// initialize pthread
	pthread_mutex_init(&mutex, NULL);
	// initialize server socket protocal
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	// set server address protocal
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	// bind
	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
	{
		error_handling("bind() error");
	}
	// listen
	if (listen(serv_sock, 5) == -1)
	{
		error_handling("listen() error");
	}

	// do service
	while (1)
	{
		// accept connection from client
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

		// record new connection
		pthread_mutex_lock(&mutex);
		clnt_socks[clnt_cnt++] = clnt_sock;
		pthread_mutex_unlock(&mutex);

		// handle the client with a new thread
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);

		// log
		printf("Connceted client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
	}
}

void * handle_clnt(void * arg)
{
	int clnt_sock = *((int*)arg);
	int str_len = 0, i;
	char msg[BUF_SIZE];

	// send the message from the client to all the clients
	while ((str_len = read(clnt_sock, msg, sizeof(msg))) != 0)
	{
		send_msg(msg, str_len);
	}

	// if client disconnected, remove the client socket from socket array
	pthread_mutex_lock(&mutex);
	for (i = 0; i < clnt_cnt; i++)
	{
		// move the disconnected socket out of range of clnt_socks
		if (clnt_sock == clnt_socks[i])
		{
			while (i++ < clnt_cnt - 1)
			{
				clnt_socks[i] = clnt_socks[i + 1];
			}
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutex);

	close(clnt_sock);
	
	return NULL;
}

// send the msg to all client
void send_msg(char * msg, int len)
{
	int i;

	pthread_mutex_lock(&mutex);
	for (i = 0; i < clnt_cnt; i++)
	{
		write(clnt_socks[i], msg, len);
	}
	pthread_mutex_unlock(&mutex);
}

void error_handling(char * msg)
{
	printf("%s\n", msg);
	abort();
}
