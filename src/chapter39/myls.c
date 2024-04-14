/* Useful interfaces: stat(), opendir(), readdir(), getcwd()*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096
#define USERNAME_SIZE 128
#define GROUPNAME_SIZE 128
#define DIR_NAMES_ARRAY_LENGTH 128

typedef struct {
    char *dir_names[DIR_NAMES_ARRAY_LENGTH];
    int dir_names_count;

    int print_hidden;
    int print_stats;
} options_t;

void swap(char **strings, int i, int j)
{
    char *tmp = strings[i];
    strings[i] = strings[j];
    strings[j] = tmp;
}

void sort(char **strings, int size, int lo, int hi, int d)
{
    if (hi <= lo) return;

    int lt = lo, gt = hi;
    int v = strings[lo][d];
    int i = lo + 1;
    while (i <= gt) {
        int t = strings[i][d];
        if (t < v) {
            swap(strings, lt++, i++);
        } else if (t > v) {
            swap(strings, i, gt--);
        } else {
            i++;
        }
    }

    sort(strings, size, lo, lt - 1, d);
    if (v >= 0) {
        sort(strings, size, lt, gt, d + 1);
    }
    sort(strings, size, gt + 1, hi, d);
}

void sort_quick_3_way(char **strings, int size)
{
    sort(strings, size, 0, size - 1, 0);
}

void parse_arguments(options_t *options, int argc, char **argv)
{
    options->dir_names_count = 0;

    options->print_hidden = 0;
    options->print_stats = 0;

    for (int i = 1; i < argc; i++) {
        char *arg_value = argv[i];
        if (*arg_value == '-') {
            arg_value++;
            while (*arg_value) {
                switch (*arg_value) {
                    case 'a': options->print_hidden = 1; break;
                    case 'l': options->print_stats = 1; break;
                }

                arg_value++;
            }
        } else {
            options->dir_names[options->dir_names_count++] = arg_value;
        }
    }

    if (options->dir_names_count == 0) {
        options->dir_names[options->dir_names_count++] = ".";
    }
}

int extract_username_from_uid(char *username, int uid)
{
    int filefd;
    if ((filefd = open("/etc/passwd", O_RDONLY, 0)) >= 0) {
        char buffer[BUFFER_SIZE] = {};
        
        int colon_end_username = 1;
        int expected_colon_start_uid = 2;
        while (read(filefd, buffer, BUFFER_SIZE) > 0) {
            char *curr = buffer;
            char *start = buffer;
            char *colon_start;
            char *colon_filename_end;

            // for every line
            while (*curr) {
                int current_colon = 0;
                while (*curr != '\n') {
                    if (*curr == ':') {
                        ++current_colon;

                        if (current_colon == expected_colon_start_uid) {
                            colon_start = curr + 1; // + 1 to skip the ':'
                        } else if (current_colon == colon_end_username) {
                            colon_filename_end = curr;
                        }
                    }

                    curr++;
                }

                int extracted_uid = atoi(colon_start);
                if (uid == extracted_uid) {
                    strncpy(username, start, (colon_filename_end - start));

                    return 0;
                }
                
                curr++;
                start = curr;
            }
        }
    }

    return -1;
}

int extract_groupname_from_gid(char *groupname, int gid)
{
    int filefd;
    if ((filefd = open("/etc/group", O_RDONLY, 0)) >= 0) {
        char buffer[BUFFER_SIZE] = {};
        
        int colon_end_username = 1;
        int expected_colon_start_gid = 2;
        while (read(filefd, buffer, BUFFER_SIZE) > 0) {
            char *curr = buffer;
            char *start = buffer;
            char *colon_start;
            char *colon_filename_end;

            // for every line
            while (*curr) {
                int current_colon = 0;
                while (*curr != '\n') {
                    if (*curr == ':') {
                        ++current_colon;

                        if (current_colon == expected_colon_start_gid) {
                            colon_start = curr + 1; // + 1 to skip the ':'
                        } else if (current_colon == colon_end_username) {
                            colon_filename_end = curr;
                        }
                    }

                    curr++;
                }

                int extracted_uid = atoi(colon_start);
                if (gid == extracted_uid) {
                    strncpy(groupname, start, (colon_filename_end - start));

                    return 0;
                }
                
                curr++;
                start = curr;
            }
        }
    }

    return -1;
}


static options_t options;

int main(int argc, char **argv)
{
    DIR             *dp;
    struct dirent   *dirp;

    parse_arguments(&options, argc, argv);

    for (int i = 0; i < options.dir_names_count; i++) {
        char *dir_name = options.dir_names[i];

        if (options.dir_names_count > 1) {
            printf("%s:\n", dir_name);
        }

        if ((dp = opendir(dir_name)) == NULL) {
            printf("%s: cannot access '%s': %s\n", argv[0], dir_name, strerror(errno));
            exit(1);
        }
        

        char *files[DIR_NAMES_ARRAY_LENGTH] = {};
        int count = 0;
        
        while ((dirp = readdir(dp)) != NULL) {
            if (options.print_hidden == 0 && *dirp->d_name == '.') {
                // Do not print hidden files/folders
            } else {
                files[count++] = dirp->d_name;
            }
        }

        sort_quick_3_way(files, count);

        for (int i = 0; i < count; i++) {
            char *file = files[i];
            if (options.print_stats == 1) {
                char file_full_pathname[BUFFER_SIZE] = {};
                snprintf(file_full_pathname, BUFFER_SIZE, "%s/%s", dir_name, file);
                
                struct stat st;
                int rc = lstat(file_full_pathname, &st);
                if (rc < 0) {
                    fprintf(stderr, "%s: cannot stat '%s': %s\n", argv[0], file_full_pathname, strerror(errno));
                    exit(EXIT_FAILURE);
                }

                char username[USERNAME_SIZE] = {};
                extract_username_from_uid(username, st.st_uid);

                char groupname[GROUPNAME_SIZE];
                extract_groupname_from_gid(groupname, st.st_gid);

                char filetype;
                switch (st.st_mode & S_IFMT) {
                    case S_IFDIR: filetype = 'd'; break;
                    case S_IFLNK: filetype = 'l'; break;
                    case S_IFREG: filetype = '-'; break;
                }

                printf("%c%c%c%c%c%c%c%c%c%c %3ld %s %s %7ld %s\n", 
                    filetype,

                    (st.st_mode & S_IRUSR ? 'r' : '-'),
                    (st.st_mode & S_IWUSR ? 'w' : '-'),
                    (st.st_mode & S_IXUSR ? 'x' : '-'),

                    (st.st_mode & S_IRGRP ? 'r' : '-'),
                    (st.st_mode & S_IWGRP ? 'w' : '-'),
                    (st.st_mode & S_IXGRP ? 'x' : '-'),

                    (st.st_mode & S_IROTH ? 'r' : '-'),
                    (st.st_mode & S_IWOTH ? 'w' : '-'),
                    (st.st_mode & S_IXOTH ? 'x' : '-'),
                    
                    st.st_nlink,

                    username,
                    groupname,
                    
                    st.st_size,
                    
                    // ctime(&st.st_atim.tv_sec),
                    
                    file);
            } else {
                printf("%s  ", file);
            }
        }


        closedir(dp);
    }

    if (options.print_stats == 0) {
        printf("\n");
    }

    return 0;
}
