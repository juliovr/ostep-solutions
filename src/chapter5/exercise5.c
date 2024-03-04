#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        printf("hello\n");
    
        // int rc_wait = wait(NULL);
        // printf("rc_wait = %d\n", rc_wait);
    
        exit(0);
    } else {
        printf("child (%d) created\n", pid);
    }


    int rc_wait = wait(NULL);
    printf("rc_wait = %d\n", rc_wait);

    printf("goodbye\n");
    
    return 0;
}
