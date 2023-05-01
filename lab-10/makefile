CC = gcc

CFLAGS = -Wall -g

all: main

main: server.out client.out


server.out: server.c
	$(CC) $^ -o $@ $(CFLAGS)

client.out: client.c
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -rf *.out