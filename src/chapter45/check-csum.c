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
#include <stdint.h>

typedef uint8_t  u8;
typedef uint16_t u16;

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

int validate_checksum(char *filename, char *checksum_file)
{
    int fd_checksum;
    if ((fd_checksum = open(checksum_file, O_RDONLY, 0)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    int fd;
    if ((fd = open(filename, O_RDONLY, 0)) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    
    int P = 0b111010101; // CRC-8
    u8 R = 0;
    char buffer[4096];
    int bytes_read;
    
    char checksum_buffer[512];
    int checksum_bytes_read;

    while ((checksum_bytes_read = read(fd_checksum, checksum_buffer, 512)) > 0) {
        for (int checksum_index = 0; checksum_index < checksum_bytes_read; checksum_index++) {
            u8 checksum_byte = checksum_buffer[checksum_index];

            if ((bytes_read = read(fd, buffer, 4096)) > 0) {
                for (int buffer_index = 0; buffer_index < bytes_read; buffer_index++) {
                    R ^= buffer[buffer_index];
                    for (int bit = 0; bit < 8; bit++) {
                        u8 leftmost_bit_set = (R & 0x80);
                        R = (R << 1);
                        if (leftmost_bit_set) {
                            R ^= P;
                        }
                    }
                }

                if (R != checksum_byte) {
                    return 0;
                }
            }
        }
    }

    close(fd);
    close(fd_checksum);

    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <checksum_file>\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];
    char *checksum_file = argv[2];
    int result = validate_checksum(filename, checksum_file);
    if (result) {
        printf("file is OK\n");
    } else {
        printf("file is corrupted\n");
    }
    
    
    return 0;
}
