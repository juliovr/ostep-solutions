#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sched.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number of pages> <number of trials>\n", argv[0]);
        exit(1);
    }

    cpu_set_t set;
    int cpu = 0;

    CPU_ZERO(&set);

    CPU_SET(cpu, &set);

    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
        fprintf(stderr, "sched_setaffinity error\n");
        exit(1);
    }

    int num_pages = atoi(argv[1]);
    int trials = atoi(argv[2]);

    long pagesize = sysconf(_SC_PAGESIZE);
    long physical_pages = sysconf(_SC_PHYS_PAGES);

    long sum = 0;
    
    for (int trial = 0; trial < trials; trial++) {
        int *a = (int *)malloc(pagesize * num_pages);

        clock_t start = clock();

        int jump = pagesize / sizeof(int);
        for (int i = 0; i < (num_pages * jump); i += jump) {
            a[i] += 1;
        }

        clock_t end = clock();

        sum += (end - start);
    }

    double elapsed = (sum / trials) * 0.001;
    printf("%.4f ms\n", elapsed);

    return 0;
}
