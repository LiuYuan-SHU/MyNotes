CC = gcc
CFLAGS = -Wall
OBJS = main.o Tools.o
INCLUDE = -Ipath

all: system delete

system: main.o Tools.o
	$(CC) $(CFLAGS) -o system $(OBJS) $(INCLUDE)
main.o: main.c NODE.h Tools.h
	gcc -c main.c
Tools.o: Tools.c NODE.h Tools.h
	gcc -c Tools.c

delete:
	rm *.o
