#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef unsigned char u8;

u8 compute_checksum(char *filename)
{
    u8 checksum = 0x0;
    int fd;
    if ((fd = open(filename, O_RDONLY, 0)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
    }

    char buffer[4096];
    int bytes_read;
    while ((bytes_read = read(fd, buffer, 4096)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            checksum ^= buffer[i];
        }
    }

    close(fd);

    return checksum;
}

int validate_file(char *filename, u8 checksum)
{
    u8 computed_checksum = compute_checksum(filename);
    return (computed_checksum == checksum);
}

// bin/check-xor test_1.txt test_2.txt
// Both files has the same content but in different order.
// The xor checksum return the same checksum for both.
int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        char *filename = argv[i];
        u8 checksum = compute_checksum(filename);

        printf("file %s: checksum = 0x%x\n", filename, checksum);
    }


    return 0;
}
