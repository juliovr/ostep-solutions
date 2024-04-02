#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"

// If done correctly, each child should print their "before" message
// before either prints their "after" message. Test by adding sleep(1)
// calls in various locations.

// You likely need two semaphores to do this correctly, and some
// other integers to track things.

typedef struct __barrier_t {
    sem_t lock;
    sem_t s;
    int sleeping_threads;
    int num_threads;
} barrier_t;


// the single barrier we are using for this program
barrier_t b;

void barrier_init(barrier_t *b, int num_threads) {
    sem_init(&b->lock, 0, 1);
    sem_init(&b->s, 0, 0);
    b->sleeping_threads = 0;
    b->num_threads = num_threads;
}

void barrier(barrier_t *b) {
    sem_wait(&b->lock);
    int sleeping_threads = ++b->sleeping_threads;
    sem_post(&b->lock);

    if (sleeping_threads < b->num_threads) {
        sem_post(&b->lock);
        sleep(1);
        sem_wait(&b->s);
    }
    
    sleep(1);
    sem_post(&b->s);
}

//
// XXX: don't change below here (just run it!)
//
typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *child(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("child %d: before\n", t->thread_id);
    barrier(&b);
    printf("child %d: after\n", t->thread_id);
    return NULL;
}


// run with a single argument indicating the number of 
// threads you wish to create (1 or more)
int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("parent: begin\n");
    barrier_init(&b, num_threads);
    
    int i;
    for (i = 0; i < num_threads; i++) {
        t[i].thread_id = i;
        Pthread_create(&p[i], NULL, child, &t[i]);
    }

    for (i = 0; i < num_threads; i++) 
        Pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}
