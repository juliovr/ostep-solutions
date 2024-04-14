#define _GNU_SOURCE          /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <unistd.h>

#include <fcntl.h>           /* Definition of AT_* constants */

#define BUFFER_SIZE 4096
#define USERNAME_SIZE 128
#define GROUPNAME_SIZE 128

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

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "%s: missing operand\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct stat st;
    int rc = lstat(argv[1], &st);
    if (rc < 0) {
        fprintf(stderr, "%s: cannot stat '%s': %s\n", argv[0], argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("  File: %s\n", argv[1]);
    printf("  Size: %ld\t\tBlocks: %ld\t\tIO Block: %ld\t\t", 
           st.st_size, st.st_blocks, st.st_blksize);
    switch (st.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }
    printf("Device: %dh/%dd  Inode: %ld  Links: %ld\n", major(st.st_dev), minor(st.st_dev), st.st_ino, st.st_nlink);
    
    char username[USERNAME_SIZE];
    extract_username_from_uid(username, st.st_uid);

    char groupname[GROUPNAME_SIZE];
    extract_groupname_from_gid(groupname, st.st_gid);

    printf("Access: (%o%o/%c%c%c%c%c%c%c%c%c%c)  Uid: (%d/%s)  Gid: (%d/%s)\n", 
           (st.st_mode & S_ISUID)|(st.st_mode & S_ISGID)|(st.st_mode & S_ISVTX),
           (st.st_mode & S_IRWXU)|(st.st_mode & S_IRWXG)|(st.st_mode & S_IRWXO), 
           
           (st.st_mode & S_IFDIR ? 'd' : '-'),

           (st.st_mode & S_IRUSR ? 'r' : '-'),
           (st.st_mode & S_IWUSR ? 'w' : '-'),
           (st.st_mode & S_IXUSR ? 'x' : '-'),

           (st.st_mode & S_IRGRP ? 'r' : '-'),
           (st.st_mode & S_IWGRP ? 'w' : '-'),
           (st.st_mode & S_IXGRP ? 'x' : '-'),

           (st.st_mode & S_IROTH ? 'r' : '-'),
           (st.st_mode & S_IWOTH ? 'w' : '-'),
           (st.st_mode & S_IXOTH ? 'x' : '-'),
           
           st.st_uid, username,
           st.st_gid, groupname);
    printf("Access: %s", ctime(&st.st_atim.tv_sec));
    printf("Modify: %s", ctime(&st.st_mtim.tv_sec));
    printf("Change: %s", ctime(&st.st_ctim.tv_sec));
    printf("Birth: -\n");
    

    return EXIT_SUCCESS;
}
