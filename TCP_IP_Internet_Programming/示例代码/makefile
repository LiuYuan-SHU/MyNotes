all : 	hello \
		low \
		tcp \
		endian \
		inet \
		echo \
		thread \
		semaphore \
		chat

hello :  hello_server hello_client	
low : low_open low_read
tcp : tcp_server tcp_client
endian : endian_conv
inet : inet_addr inet_aton inet_ntoa
echo : echo_server echo_client echo_client2
thread : thread1 thread2 thread3 thread4 mutex

hello_server : ./hello_server.c
	gcc -Wall -g -o hello_server ./hello_server.c

hello_client : ./hello_client.c
	gcc -Wall -g -o hello_client ./hello_client.c

low_open : ./low_open.c
	gcc -Wall -g -o low_open ./low_open.c

low_read : ./low_read.c
	gcc -Wall -g -o low_read ./low_read.c

tcp_server : ./tcp_server.c
	gcc -Wall -g -o tcp_server ./tcp_server.c

tcp_client : ./tcp_client.c
	gcc -Wall -g -o tcp_client ./tcp_client.c

endian_conv : ./endian_conv.c
	gcc -Wall -g -o endian_conv ./endian_conv.c

inet_addr : ./inet_addr.c
	gcc -Wall -g -o inet_addr ./inet_addr.c

inet_aton : ./inet_aton.c
	gcc -Wall -g -o inet_aton ./inet_aton.c

inet_ntoa : ./inet_ntoa.c
	gcc -Wall -g -o inet_ntoa ./inet_ntoa.c

echo_server : ./echo_server.c
	gcc -Wall -g -o echo_server ./echo_server.c

echo_client : ./echo_client.c
	gcc -Wall -g -o echo_client ./echo_client.c

echo_client2 : ./echo_client2.c
	gcc -Wall -g -o echo_client2 ./echo_client2.c

thread1 : ./thread1.c
	gcc -Wall -g -lpthread -o thread1 ./thread1.c
	
thread2 : ./thread2.c
	gcc -Wall -g -lpthread -o thread2 ./thread2.c

thread3 : ./thread3.c
	gcc -Wall -g -D_REENTRANT -lpthread -o thread3 ./thread3.c

thread4 : ./thread4.c
	gcc -Wall -g -D_REENTRANT -lpthread -o thread4 ./thread4.c

mutex : ./mutex.c
	gcc -Wall -g -D_REENTRANT -lpthread -o mutex ./mutex.c

semaphore : ./semaphore.c
	gcc -Wall -g -D_REENTRANT -lpthread -o semaphore ./semaphore.c

chat : ./chat_server.c ./chat_clnt.c
	gcc -Wall -g -D_REENTRANT -lpthread -o chat_server ./chat_server.c
	gcc -Wall -g -D_REENTRANT -lpthread -o chat_clnt ./chat_clnt.c

clean:
	-rm -rf hello_server ./hello_server.dSYM
	-rm -rf hello_client ./hello_client.dSYM
	-rm -rf low_open ./low_open.dSYM
	-rm -rf low_read ./low_read.dSYM
	-rm -rf tcp_server ./tcp_server.dSYM
	-rm -rf tcp_client ./tcp_client.dSYM
	-rm -rf endian_conv ./endian_conv.dSYM
	-rm -rf inet_addr ./inet_addr.dSYM
	-rm -rf inet_aton ./inet_aton.dSYM
	-rm -rf inet_ntoa ./inet_ntoa.dSYM
	-rm -rf echo_server ./echo_server.dSYM
	-rm -rf echo_client ./echo_client.dSYM
	-rm -rf echo_client2 ./echo_client2.dSYM
	-rm -rf thread1 ./thread1.dSYM
	-rm -rf thread2 ./thread2.dSYM
	-rm -rf thread3 ./thread3.dSYM
	-rm -rf thread4 ./thread4.dSYM
	-rm -rf mutex ./mutex.dSYM
	-rm -rf semaphore ./semaphore.dSYM
	-rm -rf chat_server ./chat_server.dSYM
	-rm -rf chat_clnt ./chat_clnt.dSYM


