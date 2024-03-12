#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define DEFAULT_TEST 64

int main(int argc, char **argv)
{
    int n_test = DEFAULT_TEST;
    if (argc > 1) {
        n_test = atoi(argv[1]);
    }

    printf("Test syscall %d times:\n", n_test);

    long start;
    long end;

    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0) {
        start = tv.tv_usec;
    }

    char buf[8];
    int n;

    for (int i = 0; i < n_test; ++i) {
        while ((n = read(STDIN_FILENO, buf, 0))) {
            printf("%s", buf);
        }
    }

    if (gettimeofday(&tv, NULL) == 0) {
        end = tv.tv_usec;

        printf("    Time elapsed = %ld usec\n", (end - start));
        printf("    Time taken by each syscall = %.4f usec\n", ((float)(end - start) / (float)n_test));
    }
    
    printf("    Test done\n");

    return 0;
}
