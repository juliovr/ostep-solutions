#include <stdio.h>
#include "common_threads.h"

int done = 0; // The condition variable
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c  = PTHREAD_COND_INITIALIZER;

void thr_exit()
{
    Pthread_mutex_lock(&m);
    done = 1;
    Pthread_cond_signal(&c); // Signal waitted threads to wake up
    Pthread_mutex_unlock(&m);
}

void *child(void *arg)
{
    printf("child\n");
    thr_exit();
    
    return NULL;
}

void thr_join()
{
    Pthread_mutex_lock(&m);
    while (done == 0) {
        Pthread_cond_wait(&c, &m); // Release the lock and put the calling thread to sleep (atomically)
    }
    Pthread_mutex_unlock(&m);
}

int main(int argc, char **argv)
{
    printf("parent: begin\n");

    pthread_t p;
    Pthread_create(&p, NULL, child, NULL);
    thr_join();

    printf("parent: end\n");

    return 0;
}
