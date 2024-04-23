#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef unsigned char u8;
typedef unsigned short u16;

u16 compute_checksum(char *filename)
{
    int fd;
    if ((fd = open(filename, O_RDONLY, 0)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
    }

    int s1 = 0;
    int s2 = 0;
    char buffer[4096];
    int bytes_read;
    while ((bytes_read = read(fd, buffer, 4096)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            s1 += buffer[i];
            s2 += s1;
        }
    }

    close(fd);

    s1 = (s1 % 255);
    s2 = (s2 % 255);

    u16 checksum = ((s1 & 0xff) << 8) | (s2 & 0xff);

    return checksum;
}

int validate_file(char *filename, u8 checksum)
{
    u8 computed_checksum = compute_checksum(filename);
    return (computed_checksum == checksum);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        char *filename = argv[i];
        u16 checksum = compute_checksum(filename);

        printf("file %s: checksum = 0x%x\n", filename, checksum);
    }
    
    return 0;
}
