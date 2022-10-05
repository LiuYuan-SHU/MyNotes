all : 	create \
		delete \
		IO	

compile_command = gcc -Wall -g -o
clean_command = -rm -rf

create : ./msgget.c
	$(compile_command) msgget msgget.c

delete : ./msgctl.c
	$(compile_command) msgctl msgctl.c

IO : ./msgIO.c
	$(compile_command) msgIO msgIO.c

clean :
	$(clean_command) msgget msgget.dSYM
	$(clean_command) msgctl msgctl.dSYM
	$(clean_command) msgIO msgIO.dSYM
