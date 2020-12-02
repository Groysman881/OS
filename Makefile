CC = gcc
CFLAGS = -o

all : l1
	./l1

l1 :
	$(CC) lab1.c $(CFLAGS) l1

