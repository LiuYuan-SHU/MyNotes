# GDB Using Notes

> GNU Debugger

## Install

1.	Method1:
	1.	`wget http://ftp.gnu.org/gnu/gdb/gdb-9.0.1.tar.gz`
	2.	`tar -zxvf gdb-9.0.1.tar.gz`
	3.	`cd gdb-9.0.1`
	4.	`./configure`
	5.	`make && make install`
2.	Method2:
	Install `gcc` & `g++`, automatly install GDB.

## Basic Debug Command

1.	(l)ist: Print source code, if `l` all the way, the following lines are printed
	+	`list n`: list code from LINE n
	+	`list function`: list code of `function`
1.	(r)un: Start the program, if no breakpoint is set, the program runs to the end.
2.	(start): Start the program and excute it step by step
7.	(b)reak: Set a breakpoint at where you want
	+	`b n`: Set a breakpoint at LINE n
	+	`b +n` / `b -n`: Set a breakpoint at the line n line before/after of current line.
	+	`b function`: Set a breakpoint at `function`
	+	`b filename:function/n`: Set a breakpoint at LINE n or `function` in `filename`
	+	`b address`: Set a breakpoint at `address`
	+	***`b ... if <condition>`***: If `condition` is true, set a breakpoint at the rule specified in `...` such like `b 9 if i = 9`. Or break the program immediately with `break if i = 3`
3.	(enable)/(disable): Enable and disable breakpoints with command `enable/disable n`. To get the ID of breakpoints, use command `info b`
4.	(d)elete: Delete breakpoints with command `d n`. 
2.	(n)ext: Excute current line and move to the next line
	+	`n n`: Excute the following n LINEs code
3.	(s)tep: Step in the function or the next line	
5.	(c)ontinue: Continue the program, till the next breakpoint	
6.	(q)uit: Quit GDB
4.	(p)rint: Print the value of expression
4.	(set): Set the value of variable
4.	(bt)backtrace: Print the stack frame and hierarchy of function calls
8.	(i)nfo: Get the information about environment and so on.
9.	(watch)/(rwatch)/(awatch): Watch variables.
	+	**watch**: 
		*	Set a watchpoint for an expression.
		*	Usage: `watch [-l|-location] EXPRESSION`. 
		*	A watchpoint stops execution of your program whenever the value of an expression changes.
	+	**rwatch**:
		* Set a read watchpoint for an expression.
		* Usage: `rwatch [-l|-location] EXPRESSION`
		* A watchpoint stops execution of your program whenever the value of an expression is read.
	+	**awatch**:
		* Set a watchpoint for an expression.
		* Usage: `awatch [-l|-location] EXPRESSION`
		* A watchpoint stops execution of your program whenever the value of an expression is either read or written.
	+	***Note***: If `-l` or `-location` is given, this evaluates EXPRESSION and watches the memory to which it refers.

## Debug Core file and running program

### Activate core, collecting the status of dumped program

> core files won't generate defautly, we have to activate it with `ulimit`

1.	list all user limits: `ulimit -a`
	```shell
	liuyuan@liuyuan-Laptop:~$ ulimit -a
	core file size          (blocks, -c) 0			<==========
	data seg size           (kbytes, -d) unlimited
	scheduling priority             (-e) 0
	file size               (blocks, -f) unlimited
	pending signals                 (-i) 30404
	max locked memory       (kbytes, -l) 65536
	max memory size         (kbytes, -m) unlimited
	open files                      (-n) 1024
	pipe size            (512 bytes, -p) 8
	POSIX message queues     (bytes, -q) 819200
	real-time priority              (-r) 0
	stack size              (kbytes, -s) 8192
	cpu time               (seconds, -t) unlimited
	max user processes              (-u) 30404
	virtual memory          (kbytes, -v) unlimited
	file locks                      (-x) unlimited
	```
2.	unlimit ***core file size*** `ulimit -c unlimited`
	```shell
	ulimit -a
	core file size          (blocks, -c) unlimited	<===========
	data seg size           (kbytes, -d) unlimited
	scheduling priority             (-e) 0
	file size               (blocks, -f) unlimited
	pending signals                 (-i) 30404
	max locked memory       (kbytes, -l) 65536
	max memory size         (kbytes, -m) unlimited
	open files                      (-n) 1024
	pipe size            (512 bytes, -p) 8
	POSIX message queues     (bytes, -q) 819200
	real-time priority              (-r) 0
	stack size              (kbytes, -s) 8192
	cpu time               (seconds, -t) unlimited
	max user processes              (-u) 30404
	virtual memory          (kbytes, -v) unlimited
	file locks                      (-x) unlimited
	```

### Debug Core file

After unlimited, generate [test code](./TestCodes/1_CoreGenerateTest/CoreGenerate.cpp) with command `g++ -g -o CoreGenerate CoreGenerate.cpp` and run it.

If succeeded, `Segmantation fault (core dumped)` will be printed, and we can find the core file at `/var/lib/apport/coredump`

Debug the core file with GDB

```shell
gdb ./CoreGenerate core_CreatedByCoreGenerate
...
Reading symbols from ./CoreGenerate...
[New LWP 4467]
Core was generated by `./CoreGenerate'.
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x0000557d331a017d in main () at CoreGenerate.cpp:8
8		*p = 5;
```

### Debug running program

https://www.bilibili.com/video/BV1EK411g7Li?p=7