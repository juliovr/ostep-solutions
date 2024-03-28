CC = gcc
CFLAGS = -Og -g -Wall -pthread

all: main-race

main-race: main-race.c common_threads.h
	$(CC) $(CFLAGS) -o bin/main-race main-race.c

helgrind_main-race: main-race
	valgrind --tool=helgrind bin/main-race

main-deadlock: main-deadlock.c common_threads.h
	$(CC) $(CFLAGS) -o bin/main-deadlock main-deadlock.c

helgrind_main-deadlock: main-deadlock
	valgrind --tool=helgrind bin/main-deadlock

main-deadlock-global: main-deadlock-global.c common_threads.h
	$(CC) $(CFLAGS) -o bin/main-deadlock-global main-deadlock-global.c

helgrind_main-deadlock-global: main-deadlock-global
	valgrind --tool=helgrind bin/main-deadlock-global

main-signal: main-signal.c common_threads.h
	$(CC) $(CFLAGS) -o bin/main-signal main-signal.c

helgrind_main-signal: main-signal
	valgrind --tool=helgrind bin/main-signal

main-signal-cv: main-signal-cv.c common_threads.h
	$(CC) $(CFLAGS) -o bin/main-signal-cv main-signal-cv.c

helgrind_main-signal-cv: main-signal-cv
	valgrind --tool=helgrind bin/main-signal-cv
