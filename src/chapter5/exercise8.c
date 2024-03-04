#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        fprintf(stderr, "pipe error\n");
        exit(1);
    }

    pid_t pid_child_write;
    pid_t pid_child_read;
    
    if ((pid_child_read = fork()) == 0) {
        close(pipe_fd[1]); // Close unused write end

        char buf[128];
        while (read(pipe_fd[0], buf, 128)) {
            printf("%s\n", buf);
        }

        close(pipe_fd[0]);

        exit(0);
    }

    if ((pid_child_write = fork()) == 0) {
        close(pipe_fd[0]); // Close unused read end

        char buf[128] = "data from pipe\n";
        int rc = write(pipe_fd[1], buf, strlen(buf));

        close(pipe_fd[1]);

        exit(0);
    }
    
    return 0;
}
