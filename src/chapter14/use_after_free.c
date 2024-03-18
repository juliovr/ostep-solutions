/*
valgrind --leak-check=yes bin/use_after_free
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int *x = (int *)malloc(100 * sizeof(int));
    free(x);

    x[0] = 5;

    return 0;
}
