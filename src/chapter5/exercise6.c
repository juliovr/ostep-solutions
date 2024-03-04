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
    
        exit(0);
    } else {
        printf("child (%d) created\n", pid);
    }


    int wstatus;
    int rc_wait = waitpid(pid, &wstatus, 0);
    printf("wstatus = %d, rc_wait = %d\n", wstatus, rc_wait);

    printf("goodbye\n");
    
    return 0;
}
