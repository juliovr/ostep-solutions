CC = gcc
CFLAGS = -Og -g

all: check-xor check-fletcher check-crc16 create-csum check-csum

check-xor: check-xor.c
	$(CC) $(CFLAGS) -o bin/check-xor check-xor.c

check-fletcher: check-fletcher.c
	$(CC) $(CFLAGS) -o bin/check-fletcher check-fletcher.c

check-crc16: check-crc16.c
	$(CC) $(CFLAGS) -o bin/check-crc16 check-crc16.c

create-csum: create-csum.c
	$(CC) $(CFLAGS) -o bin/create-csum create-csum.c

check-csum: check-csum.c
	$(CC) $(CFLAGS) -o bin/check-csum check-csum.c
