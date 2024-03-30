CC = gcc
CFLAGS = -Og -g

all: test_timers simple_counter approximate_counter linked_list linked_list_hand_over_hand_locking

test_timers: test_timers.c
	$(CC) $(CFLAGS) -o bin/test_timers test_timers.c

simple_counter: simple_counter.c
	$(CC) $(CFLAGS) -o bin/simple_counter simple_counter.c

approximate_counter: approximate_counter.c
	$(CC) $(CFLAGS) -o bin/approximate_counter approximate_counter.c

linked_list: linked_list.c
	$(CC) $(CFLAGS) -o bin/linked_list linked_list.c

linked_list_hand_over_hand_locking: linked_list_hand_over_hand_locking.c
	$(CC) $(CFLAGS) -o bin/linked_list_hand_over_hand_locking linked_list_hand_over_hand_locking.c
