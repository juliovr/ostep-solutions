#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <time.h>
#include "common_threads.h"

typedef struct node_t {
    int             value;
    struct node_t   *next;
} node_t;

typedef struct list_t {
    node_t          *head;
    pthread_mutex_t mutex;
} list_t;


static int ncores;
static list_t list;

void list_init(list_t *list)
{
    list->head = NULL;
    Pthread_mutex_init(&list->mutex, NULL);
}

void list_insert(list_t *list, int value)
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    assert(new_node);

    new_node->value = value;

    Pthread_mutex_lock(&list->mutex);
    new_node->next = list->head;
    list->head = new_node;
    Pthread_mutex_unlock(&list->mutex);
}

int list_lookup(list_t *list, int value)
{
    int exists = 0;

    Pthread_mutex_lock(&list->mutex);
    for (node_t *current = list->head; current; current = current->next) {
        if (current->value == value) {
            exists = 1;
            break;
        }
    }
    Pthread_mutex_unlock(&list->mutex);

    return exists;
}


void *worker_thread(void *arg)
{
    int sample_size = *((int *)arg);

    for (int i = 0; i < sample_size; i++) {
        list_insert(&list, i);
    }
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
    
    list_init(&list);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

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
