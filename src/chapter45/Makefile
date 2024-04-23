CC = gcc
CFLAGS = -Og -g

all: check-xor check-fletcher check-crc16

check-xor: check-xor.c
	$(CC) $(CFLAGS) -o bin/check-xor check-xor.c

check-fletcher: check-fletcher.c
	$(CC) $(CFLAGS) -o bin/check-fletcher check-fletcher.c

check-crc16: check-crc16.c
	$(CC) $(CFLAGS) -o bin/check-crc16 check-crc16.c
