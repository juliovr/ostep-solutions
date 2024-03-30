#include <stdio.h>
#include <unistd.h>
#include <immintrin.h>
#include <time.h>

int main(int argc, char **argv)
{
#if 0
    long long start = _rdtsc();
    printf("rdtsc = %lld\n", start);
    
    sleep(1);

    long long end = _rdtsc();
    printf("rdtsc = %lld\n", end);

    long long diff = (end - start);
    printf("diff = %lld\n", diff);

    printf("time = %lld sec\n", diff/60);
#endif

    clock_t start = clock();

    for (int i = 0; i < 900100000; ++i)
        ;

    clock_t end = clock();

    printf("diff = %ld ms\n", (end - start) * 0.001);
    printf("diff = %f seconds\n", (float)(end - start)/(float)CLOCKS_PER_SEC);

    return 0;
}
