CC = gcc
CFLAGS = -Og -g

all: client server

client: client.c
	$(CC) $(CFLAGS) -o bin/client client.c

server: server.c
	$(CC) $(CFLAGS) -o bin/server server.c
