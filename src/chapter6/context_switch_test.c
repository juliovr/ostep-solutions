#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    cpu_set_t set;
    int cpu = 0;

    CPU_ZERO(&set);

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }

    pid_t pid_child_write;
    pid_t pid_child_read;
    
    long start;
    long end;

    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0) {
        start = tv.tv_usec;
    }

    if ((pid_child_read = fork()) == 0) {
        CPU_SET(cpu, &set);

        if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
            fprintf(stderr, "sched_setaffinity error\n");
            exit(1);
        }


        close(pipe_fd[1]); // Close unused write end

        char buf[128];
        while (read(pipe_fd[0], buf, 128)) {
            printf("%s\n", buf);
        }

        close(pipe_fd[0]);

        exit(0);
    }

    if ((pid_child_write = fork()) == 0) {
        CPU_SET(cpu, &set);

        if (sched_setaffinity(getpid(), sizeof(set), &set) == -1) {
            fprintf(stderr, "sched_setaffinity error\n");
            exit(1);
        }


        close(pipe_fd[0]); // Close unused read end

        char buf[128] = "data from pipe\n";
        int rc = write(pipe_fd[1], buf, strlen(buf));

        close(pipe_fd[1]);

        exit(0);
    }

    if (gettimeofday(&tv, NULL) == 0) {
        end = tv.tv_usec;

        printf("    Time elapsed = %ld usec\n", (end - start));
        printf("    Time taken by each syscall = %ld usec\n", (end - start));
    }
    
    printf("    Test done\n");


    return 0;
}
