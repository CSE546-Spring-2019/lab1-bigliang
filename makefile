#makefile for hello.c

CC=gcc
CGLAGS = -g -Wall

all: count
count: count.c
	$(CC) $(CFLAGS) -o count count.c

clean:
	rm count
