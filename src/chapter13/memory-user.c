#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s <bytes_memory> <sleep_seconds>\n", argv[0]);
        exit(1);
    }

    printf("Running PID = %d\n", getpid());

    int bytes_count = atoi(argv[1]);
    int seconds = atoi(argv[2]);

    char *bytes = malloc(bytes_count);

    printf("Location of bytes: %p\n", bytes);
    printf("Location of bytes_count (stack): %p\n", &bytes_count);
    
    for (int i = 0; i < bytes_count; ++i) {
        bytes[i] = i;
    }

    for (int i = 0; i < bytes_count; ++i) {
        printf("bytes[%d] = %d\n", i, bytes[i]);
    }

    sleep(seconds);

    return 0;
}
