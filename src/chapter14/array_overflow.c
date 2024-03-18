/*
valgrind --leak-check=yes bin/array_overflow
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int *x = (int *)malloc(100 * sizeof(int));

    x[100] = 0;

    return 0;
}
