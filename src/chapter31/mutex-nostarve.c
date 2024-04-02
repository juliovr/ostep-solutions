#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
    sem_t mutex;
    sem_t room_1;
    sem_t room_2;
    int count_room_1;
    int count_room_2;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m) {
    sem_init(&m->mutex, 0, 1);
    sem_init(&m->room_1, 0, 1);
    sem_init(&m->room_2, 0, 0);
    m->count_room_1 = 0;
    m->count_room_2 = 0;
}

void ns_mutex_acquire(ns_mutex_t *m) {
    //
    // Enters room 1
    //
    sem_wait(&m->mutex);
    m->count_room_1++;
    sem_post(&m->mutex);

    sem_wait(&m->room_1);

    //
    // Go to room 2
    //
    sem_wait(&m->mutex);
    m->count_room_2++; // Enters room 2
    m->count_room_1--; //     ...by leaving room 1

    if (m->count_room_1 == 0) {
        sem_post(&m->mutex);
        sem_post(&m->room_2);   // When there are no more threads in room 1, it will wake threads waiting to be process in room 2 (line 57: sem_wait(&->room_2))
    } else {                    
        sem_post(&m->mutex);
        sem_post(&m->room_1);   // Ensure all threads waiting on line 37 (sem_wait(&m->room_1)) go to room 2
    }


    sem_wait(&m->room_2); // Acquiring the lock in room 2 it will process the critical section
}

void ns_mutex_release(ns_mutex_t *m) {
    sem_wait(&m->mutex);
    m->count_room_2--; // Remove from room 2
    if (m->count_room_2 == 0) {
        sem_post(&m->mutex);
        sem_post(&m->room_1); // When there are no more threads in room 2, just signal room 1 to let threads go to room 2
    } else {
        sem_post(&m->mutex);
        sem_post(&m->room_2); // Process remaining threads waiting in room 2
    }
}


ns_mutex_t mutex;

void *worker(void *arg) {
    int tid = (int)arg;
    int times = 10;
    
    while (times--) {
        ns_mutex_acquire(&mutex);
        printf("child %d: begin\n", tid);
        printf("child %d: end\n", tid);
        ns_mutex_release(&mutex);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

    ns_mutex_init(&mutex);

    printf("parent: begin\n");

    Pthread_create(&t1, NULL, worker, 1);
    Pthread_create(&t2, NULL, worker, 2);
    Pthread_create(&t3, NULL, worker, 3);

    Pthread_join(t1, NULL);
    Pthread_join(t2, NULL);
    Pthread_join(t3, NULL);

    printf("parent: end\n");

    return 0;
}
