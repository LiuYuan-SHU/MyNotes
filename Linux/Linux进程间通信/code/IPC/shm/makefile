all : shmget IO delete example

compile_command = gcc -Wall -g -o
clean_command = -rm -rf 

shmget : ./shmget.c
	$(compile_command) shmget shmget.c
	gcc -Wall -g -D_FTOK -o shmget_ftok shmget.c
	touch shm.txt

IO : ./shmget_IO.c
	$(compile_command) shmget_IO shmget_IO.c

delete : ./shmdt.c ./shmctl.c
	$(compile_command) shmdt shmdt.c
	$(compile_command) shmctl shmctl.c

example : ./communicate_with_child.c ./clnt.c ./serv.c
	$(compile_command) communicate_with_child communicate_with_child.c
	$(compile_command) clnt clnt.c
	$(compile_command) serv serv.c
	touch shm.txt

clean :
	$(clean_command) shmget shmget.dSYM
	$(clean_command) shmget_ftok shmget_ftok.dSYM shm.txt
	$(clean_command) shmget_IO shmget_IO.dSYM
	$(clean_command) shmdt shmdt.dSYM
	$(clean_command) shmctl shmctl.dSYM
	$(clean_command) communicate_with_child communicate_with_child.dSYM
	$(clean_command) clnt clnt.dSYM serv serv.dSYM shm.txt
