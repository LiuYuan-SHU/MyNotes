all :	mykill  \
		raise1 raise2 \
		alarm \
		pause \
		signal_test

compile_command = gcc -Wall -g -o
clean_command = -rm -rf

mykill : ./mykill.c
	$(compile_command) mykill mykill.c

raise1 : ./raise.c
	$(compile_command) raise raise.c
raise2 : ./raise_2.c
	$(compile_command) raise_2 raise_2.c

alarm : ./alarm.c
	$(compile_command) alarm alarm.c

pause : ./pause.c
	$(compile_command) pause pause.c

signal_test : signal_SIGIGN signal_SIGDFL signal
signal_SIGIGN : ./signal_SIGIGN.c
	$(compile_command) signal_SIGIGN signal_SIGIGN.c
signal_SIGDFL : ./signal_SIGDFL.c
	$(compile_command) signal_SIGDFL signal_SIGDFL.c
signal : ./signal.c
	$(compile_command) signal signal.c

clean : 
	$(clean_command) mykill mykill.dSYM
	$(clean_command) raise raise.dSYM
	$(clean_command) raise_2 raise_2.dSYM
	$(clean_command) alarm alarm.dSYM
	$(clean_command) pause pause.dSYM
	$(clean_command) signal signal.dSYM
	$(clean_command) signal_SIGIGN signal_SIGIGN.dSYM
	$(clean_command) signal_SIGDFL signal_SIGDFL.dSYM
