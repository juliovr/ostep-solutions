#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "common_threads.h"

typedef struct counter_t {
    int             global;
    pthread_mutex_t glock;
    int             *local;
    pthread_mutex_t *llock;
    int             threshold;
} counter_t;

static counter_t counter;
static int ncores;


void init(counter_t *c, int ncores, int threshold)
{
    c->global = 0;
    c->threshold = threshold;
    c->local = (int *)malloc(ncores * sizeof(int));
    c->llock = (pthread_mutex_t *)malloc(ncores * sizeof(pthread_mutex_t));

    for (int i = 0; i < ncores; i++) {
        c->local[i] = 0;
        Pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(counter_t *c, int amount)
{
    int cpu = gettid() % ncores;

    Pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amount;
    if (c->local[cpu] >= c->threshold) {
        Pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        Pthread_mutex_unlock(&c->glock);

        c->local[cpu] = 0;
    }
    Pthread_mutex_unlock(&c->llock[cpu]);
}

void increment(counter_t *c)
{
    update(c, 1);
}

void decrement(counter_t *c)
{
    update(c, -1);
}

int get(counter_t *c)
{
    Pthread_mutex_lock(&c->glock);
    int value = c->global;
    Pthread_mutex_unlock(&c->glock);

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

    ncores = (int)sysconf(_SC_NPROCESSORS_CONF);
    int nthreads = atoi(argv[1]);
    int total_sample_size = atoi(argv[2]);
    int sample_size_per_thread = total_sample_size / nthreads;
    int threshold = 10000;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    init(&counter, ncores, threshold);

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
