CC = gcc
CFLAGS = -Og -g

all: syscall_test context_switch_test

syscall_test: syscall_test.c
	$(CC) $(CFLAGS) -o bin/syscall_test syscall_test.c

context_switch_test: context_switch_test.c
	$(CC) $(CFLAGS) -o bin/context_switch_test context_switch_test.c
