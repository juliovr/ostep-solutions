/*
Computes a single-byte checksum for every 4KB block of a file, and records the results in
the output file specified on the command line.
*/
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

u16 compute_checksum(char *input_filename, char *output_filename)
{
    int fd;
    if ((fd = open(input_filename, O_RDONLY, 0)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    int output_fd;
    if ((output_fd = open(output_filename, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    int P = 0b111010101; // CRC-8
    u8 R = 0;
    char buffer[4096];
    int bytes_read;
    while ((bytes_read = read(fd, buffer, 4096)) > 0) {
        for (int i = 0; i < bytes_read; i++) {
            R ^= buffer[i];
            for (int bit = 0; bit < 8; bit++) {
                u8 leftmost_bit_set = (R & 0x80);
                R = (R << 1);
                if (leftmost_bit_set) {
                    R ^= P;
                }
            }
        }

        printf("R = %d\n", R);

        if (write(output_fd, &R, sizeof(u8)) < 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            exit(1);
        }
    }

    close(output_fd);
    close(fd);

    u16 checksum = R;

    return checksum;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_filename> <output_checksums_filename>\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];
    char *output = argv[2];
    u16 checksum = compute_checksum(filename, output);

    
    return 0;
}
