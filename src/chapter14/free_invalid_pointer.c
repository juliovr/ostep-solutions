/*
valgrind --leak-check=yes bin/free_invalid_pointer
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int *x = (int *)malloc(100 * sizeof(int));
    int *y = (x + 1);
    free(y);

    x[0] = 5;

    return 0;
}
