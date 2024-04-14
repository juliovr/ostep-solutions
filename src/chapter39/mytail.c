/* Useful interfaces: stat(), lseek(), open(), read(), close() */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <fcntl.h>


#define BUFFER_SIZE 4096
#define FILES_ARRAY_LENGTH 16
#define MIN(a, b) ((a < b) ? (a) : (b))

int isnumber(char *string)
{
    while (*string) {
        if (*string < '0' || *string > '9') {
            return 0;
        }

        string++;
    }

    return 1;
}


int main(int argc, char **argv)
{
    int lines = 10;
    char *files[FILES_ARRAY_LENGTH] = {};
    int count = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-n] <filename>\n", argv[0]);
        exit(1);
    }

    if (argc < 3) {
        files[count++] = argv[1];
    } else if (argc >= 3) {
        char *arg_value = argv[1];
        if (*arg_value == '-') {
            arg_value++;
            if (!isnumber(arg_value)) {
                fprintf(stderr, "%s: invalid option -- '%s'\n", argv[0], arg_value);
                exit(1);
            }

            lines = atoi(arg_value);
        } else {
            for (int i = 1; i < argc; i++) {
                files[count++] = argv[i];
            }
        }
    }

    int lines_to_search = lines + 1;

    for (int file_index = 0; file_index < count; file_index++) {
        char *filename = files[file_index];

        struct stat st;
        int rc = lstat(filename, &st);
        if (rc < 0) {
            fprintf(stderr, "%s: cannot stat '%s': %s\n", argv[0], argv[1], strerror(errno));
            exit(EXIT_FAILURE);
        }

        int filefd;
        off_t offset;
        if ((filefd = open(filename, O_RDONLY, 0)) >= 0) {
            off_t lseek_offset = st.st_size / 2;
            while (1) {
                offset = lseek(filefd, -lseek_offset, SEEK_END);
                if (offset < 0) {
                    fprintf(stderr, "%s: cannot lseek: %s, line = %d\n", argv[0], strerror(errno), __LINE__);
                    exit(EXIT_FAILURE);
                }
                
                char buffer[BUFFER_SIZE] = {};
                int bytes_read;
                
                int linefeeds = 0;
                while ((bytes_read = read(filefd, buffer, BUFFER_SIZE)) > 0) {
                    for (int i = 0; i < bytes_read; i++) {
                        if (buffer[i] == '\n') {
                            linefeeds++;
                        }
                    }
                }

                if (lseek_offset == st.st_size || linefeeds == lines_to_search) {
                    offset = lseek(filefd, -lseek_offset, SEEK_END);
                    int skip_first_linefeed;
                    if (lseek_offset == st.st_size) {
                        skip_first_linefeed = 0;
                    } else {
                        skip_first_linefeed = 1;
                    }

                    if (count > 1) {
                        printf("==> %s <==\n", filename);
                    }

                    while ((bytes_read = read(filefd, buffer, BUFFER_SIZE)) > 0) {
                        char *string = buffer;
                        if (skip_first_linefeed) {
                            while (bytes_read > 0 && *string && *string != '\n') {
                                bytes_read--;
                                string++;
                            }
                            string++; // Skip last line-feed

                            skip_first_linefeed = 0;
                        }

                        write(1, string, bytes_read);
                    }
                    break;
                } else if (linefeeds < lines_to_search) {
                    lseek_offset = MIN(lseek_offset + (lseek_offset / 2), st.st_size);
                } else {
                    lseek_offset = MIN(lseek_offset / 2, st.st_size);
                }
            }

            close(filefd);
        }
    }


    return EXIT_SUCCESS;
}
