#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        close(STDOUT_FILENO);
        printf("hello\n");
    
        exit(0);
    } else {
        printf("child (%d) created\n", pid);
    }

    printf("goodbye\n");
    
    return 0;
}
