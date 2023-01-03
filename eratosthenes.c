#define _GNU_SOURCE

#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include "common.h"
#include "methods.h"

clock_t eratosthenes(_Bool** primes, ull* primes_max)
{
    clock_t begin = clock();
    for(ull i = 2; i < isqrt(*primes_max); ++i)
    {
        if((*primes)[i])
        {
            for(ull c = 2, j = 0; j < *primes_max; j = (i * c), ++c)
            {
                (*primes)[j] = 0;
            }
        }
    }

    return begin;
}

