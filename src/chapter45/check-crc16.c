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

void print_bits(long n)
{
    char bits[65];
    bits[64] = '\0';
    int i;
    for (i = 63; i >= 0; i--) {
        bits[i] = '0' + (n & 1);
        n >>= 1;
    }

    printf("%s\n", bits);
}

u16 compute_checksum(char *filename)
{
    int fd;
    if ((fd = open(filename, O_RDONLY, 0)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    int P = (0xC002 << 1) | 1;
    int R = 0;
    char buffer[4096];
    int bytes_read;
    while ((bytes_read = read(fd, buffer, 4096)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            R ^= buffer[i];
            for (int bit = 0; bit < 8; bit++) {
                int leftmost_bit_set = (R & 0x80);
                R = (R << 1) & 0xFF;
                if (leftmost_bit_set) {
                    R ^= P;
                }
            }
        }
    }

    close(fd);

    u16 checksum = R;

    return checksum;
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
