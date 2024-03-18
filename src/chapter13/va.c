#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("Location of code   : %p\n", (void *)main);
    printf("Location of heap   : %p\n", (void *)malloc(1));
    int x = 5;
    printf("Location of stack  : %p\n", (void *)&x);
    
    return 0;
}
