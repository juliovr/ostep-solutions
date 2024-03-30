#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "common_threads.h"

typedef struct counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

static counter_t counter;


void init(counter_t *c)
{
    c->value = 0;
    Pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    c->value++;
    Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    c->value--;
    Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c)
{
    Pthread_mutex_lock(&c->lock);
    int value = c->value;
    Pthread_mutex_unlock(&c->lock);

    return value;
}


void *worker_thread(void *arg)
{
    int sample_size = *((int *)arg);

    for (int i = 0; i < sample_size; i++) {
        increment(&counter);
    }

    return NULL;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <nthreads> <total_sample_size>\n", argv[0]);
        exit(1);
    }

    int nthreads = atoi(argv[1]);
    int total_sample_size = atoi(argv[2]);
    int sample_size_per_thread = total_sample_size / nthreads;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    init(&counter);

    pthread_t *threads = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
    for (int i = 0; i < nthreads; i++) {
        pthread_t *p = threads + i;
        Pthread_create(p, NULL, worker_thread, &sample_size_per_thread);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_t p = threads[i];
        Pthread_join(p, NULL);
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    float elapsed = (((float)(end.tv_nsec - start.tv_nsec) / 1000000000.0)
                    + (end.tv_sec - start.tv_sec));
    printf("elapsed time = %.4f sec\n", elapsed);

    return 0;
}
