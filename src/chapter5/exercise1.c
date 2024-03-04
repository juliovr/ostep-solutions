#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int x = 100;

    pid_t pid = fork();
    if (pid == 0) {
        x += 10;
        printf("child x = %d\n", x);
        exit(0);
    }

    printf("x = %d\n", x);
    
    return 0;
}
