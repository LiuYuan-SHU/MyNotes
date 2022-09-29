all : create IO_single block communicate

command = gcc -Wall -g -o
command_clean = -rm -rf 

create : ./create.c
	$(command) create ./create.c

IO_single : ./IO_single.c
	$(command) IO_single ./IO_single.c

block : block_read block_write
block_read : ./block_read.c
	$(command) block_read ./block_read.c
block_write : ./block_write.c
	$(command) block_write ./block_write.c

communicate : ./communicate.c
	$(command) communicate ./communicate.c

clean : 
	$(command_clean) create ./create.dSYM
	$(command_clean) IO_single ./IO_single.dSYM
	$(command_clean) block_read ./block_read.dSYM
	$(command_clean) block_write ./block_write.dSYM
	$(command_clean) communicate ./communicate.dSYM
