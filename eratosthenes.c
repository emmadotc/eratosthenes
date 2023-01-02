#define _GNU_SOURCE

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include "common.h"
#include "methods.h"

clock_t eratosthenes(ull primes_stop, _Bool** primes, ull* array_max)
{
    ull old_size = SIZEP;
    *array_max = primes_stop;
    *primes = mremap((*primes), old_size, SIZEP, MREMAP_MAYMOVE);
    if(*primes == MAP_FAILED)
    {
        perror("mmap");
        return -2;
    }

    for(ull i = 0; i < *array_max; ++i)
    {
        (*primes)[i] = 1;
    }
    (*primes)[0] = 0;
    (*primes)[1] = 0;

    clock_t begin = clock();
    for(ull i = 2; i < isqrt(*array_max); ++i)
    {
        if((*primes)[i])
        {
            for(ull c = 2, j = 0; j < *array_max; j = (i * c), ++c)
            {
                (*primes)[j] = 0;
            }
        }
    }

    return begin;
}

