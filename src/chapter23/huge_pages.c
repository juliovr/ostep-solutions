#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
    int length = 1024;

    void *memory = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    int rc = munmap(memory, length);

    if (rc == 0) {
        printf("Done\n");
    } else {
        printf("Error %d: %s\n", errno, strerror(errno));
    }

    return 0;
}
