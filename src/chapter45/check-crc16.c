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

int custom_pow(int a, int b)
{
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }

    return result;
}

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

void print_binary_array(int array[], int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
    }
    printf("\n");
}

u16 compute_checksum(char *filename)
{
    // int fd;
    // if ((fd = open(filename, O_RDONLY, 0)) < 0) {
    //     fprintf(stderr, "%s\n", strerror(errno));
    // }

    // int s1 = 0;
    // int s2 = 0;
    // char buffer[4096];
    // int bytes_read;
    // while ((bytes_read = read(fd, buffer, 4096)) > 0) {
    //     for (int i = 0; i < bytes_read; i++) {
    //         s1 += buffer[i];
    //         s2 += s1;
    //     }
    // }

    // close(fd);

    long P = 0b100000111;
    int n = 9;
    int w = n - 1;
    u8 M[] = {
        1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 
    };
    int len_m = 32;
    u16 checksum = 0;

    int R[w];
    memset(R, 0, sizeof(R));
    
    for (int i = 0; i < len_m; i++) {
        R[0] ^= M[i];
        int leftmost_bit_set = (R[0] == 1);
        
        // shift left by 1
        int r_index;
        for (r_index = 0; r_index < w - 1; r_index++) {
            R[r_index] = R[r_index + 1];
        }
        R[r_index] = 0;

        if (leftmost_bit_set) {
            for (int j = 0; j < w; j++) {
                R[j] ^= ((P >> w - 1 - j) & 1);
            }
        }
    }

    int shift = w - 1;
    for (int i = 0; i < w; i++) {
        checksum |= (R[i] << shift);
        shift--;
    }

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
        // print_bits(checksum);
        int expected = 0b11011110; // 0xde
        if (expected == checksum) {
            printf("valid\n");
        } else {
            printf("not valid!, expected = 0x%x -> ", expected);
            print_bits(expected);
        }
    }
    
    return 0;
}
