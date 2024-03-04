#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// #include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        printf("hello\n");
        exit(0);
    }

    // Openning a file cause the cpu to schedule the child (instead of using wait, as the exercise says so).
    int fd = open("test_file", O_RDONLY, S_IRWXU);

    printf("goodbye\n");
    
    return 0;
}
