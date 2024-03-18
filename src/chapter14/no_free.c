/*
valgrind --leak-check=yes bin/no_free
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int *x = (int *)malloc(sizeof(int));

    *x = 5;

    printf("x = %d\n", *x);

    return 0;
}
