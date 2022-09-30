all : mykill raise1 raise2

compile_command = gcc -Wall -g -o
clean_command = -rm -rf

mykill : ./mykill.c
	$(compile_command) mykill mykill.c

raise1 : ./raise.c
	$(compile_command) raise raise.c
raise2 : ./raise_2.c
	$(compile_command) raise_2 raise_2.c

clean : 
	$(clean_command) mykill mykill.dSYM
	$(clean_command) raise raise.dSYM
	$(clean_command) raise_2 raise_2.dSYM
