/*
valgrind --leak-check=yes bin/null
*/

#include <stdio.h>

int main(int argc, char **argv)
{
    int *x = NULL;

    *x = 5;

    return 0;
}
