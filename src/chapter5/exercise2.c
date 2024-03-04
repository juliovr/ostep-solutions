#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("test_file", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    pid_t pid = fork();
    if (pid == 0) {
        char buf_child[128] = "test data from child\n";
        write(fd, buf_child, strlen(buf_child));
        close(fd);
        exit(0);
    }

    char buf_parent[128] = "test data from parent\n";
    write(fd, buf_parent, strlen(buf_parent));
    close(fd);
    
    return 0;
}
