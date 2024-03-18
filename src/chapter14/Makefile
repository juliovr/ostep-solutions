CC = gcc
CFLAGS = -Og -g

all: null no_free array_overflow use_after_free free_invalid_pointer

null: null.c
	$(CC) $(CFLAGS) -o bin/null null.c

no_free: no_free.c
	$(CC) $(CFLAGS) -o bin/no_free no_free.c

array_overflow: array_overflow.c
	$(CC) $(CFLAGS) -o bin/array_overflow array_overflow.c

use_after_free: use_after_free.c
	$(CC) $(CFLAGS) -o bin/use_after_free use_after_free.c

free_invalid_pointer: free_invalid_pointer.c
	$(CC) $(CFLAGS) -o bin/free_invalid_pointer free_invalid_pointer.c
