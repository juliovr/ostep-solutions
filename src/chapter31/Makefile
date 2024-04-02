CC = gcc
CFLAGS = -Og -g

all: fork-join rendezvous barrier reader-writer mutex-nostarve

fork-join: fork-join.c
	$(CC) $(CFLAGS) -o bin/fork-join fork-join.c

rendezvous: rendezvous.c
	$(CC) $(CFLAGS) -o bin/rendezvous rendezvous.c

barrier: barrier.c
	$(CC) $(CFLAGS) -o bin/barrier barrier.c

reader-writer: reader-writer.c
	$(CC) $(CFLAGS) -o bin/reader-writer reader-writer.c

mutex-nostarve: mutex-nostarve.c
	$(CC) $(CFLAGS) -o bin/mutex-nostarve mutex-nostarve.c
