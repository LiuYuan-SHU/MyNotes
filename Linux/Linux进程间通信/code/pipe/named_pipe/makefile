all : create pipe

compile_command = gcc -Wall -g -o
clean_command = -rm -rf

create : create.c
	$(compile_command) create ./create.c

pipe : pipe_read pipe_write create
pipe_read : pipe_read.c
	$(compile_command) pipe_read ./pipe_read.c
pipe_write : pipe_write.c
	$(compile_command) pipe_write ./pipe_write.c

clean : 
	$(clean_command) create create.dSYM	./myfifo
	$(clean_command) pipe_write pipe_write.dSYM
	$(clean_command) pipe_read pipe_read.dSYM
