all : 	create \
		delete \
		thread \
		serv_clnt

compile_command = -gcc -Wall -g -o
sem_compile = gcc -Wall -g -D_REENTRANT -lpthread -o 
clean_command = -rm -rf

create : ./semget.c
	$(compile_command) semget semget.c

delete : ./semctl.c
	$(compile_command) semctl semctl.c

thread : ./thread_POSIX.c ./thread_sem.c
	$(sem_compile) thread_POSIX thread_POSIX.c
	$(sem_compile) thread_sem thread_sem.c

serv_clnt : ./server.c ./client.c
	$(sem_compile) server server.c
	$(sem_compile) client client.c
	touch sem.txt

clean :
	$(clean_command) semget semget.dSYM
	$(clean_command) semctl semctl.dSYM
	$(clean_command) thread_POSIX thread_POSIX.dSYM
	$(clean_command) thread_sem thread_sem.dSYM
	$(clean_command) server server.dSYM
	$(clean_command) client client.dSYM
	$(clean_command) sem.txt
