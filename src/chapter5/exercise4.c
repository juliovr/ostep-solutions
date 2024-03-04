#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/ls", "", "-l", NULL);

        exit(0);
    }
    
    return 0;
}
