#define _GNU_SOURCE

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mman.h>

#include "args.h"
#include "common.h"
#include "methods.h"

void show_help(char* argv0)
{
    fprintf(stderr,
            "Usage: %s range [args]\n"
            "  Check primes from 0 to range (Maximum %llu)\n\n"

            "Args:"
            "    -p, --print        Print primes found\n",
            argv0,
            ULLONG_MAX);
}

int main(int argc, char** argv)
{
    if(argc <= 1)
    {
        show_help(argv[0]);
        return EXIT_FAILURE;
    }

    _Args args;
    init_args(&args);
    if(!parse_args(argc, argv, &args))
    {
        show_help(argv[0]);
        return EXIT_FAILURE;
    }

    /* check primes up to primes_stop */
    ull primes_max = strtoull(argv[1], NULL, 10);
    if(primes_max == 0)
    {
        show_help(argv[0]);
        return EXIT_FAILURE;
    }

    _Bool *primes = malloc(SIZE);
    if(primes == NULL)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }

    // init array
    for(ull i = 0; i < primes_max; ++i)
    {
        primes[i] = 1;
    }
    primes[0] = 0;
    primes[1] = 0;

    clock_t begin_primes = eratosthenes(&primes, &primes_max);
    if(begin_primes == -1)
    {
        free(primes);
        return EXIT_FAILURE;
    }
    clock_t end_primes = clock();

    clock_t begin_print = clock();
    if(args.printing)
    {
        for(ull primes_indx = 0; primes_indx < primes_max; ++primes_indx)
            if(primes[primes_indx])
            /* TODO: optimise printing */
                printf("%llu\n", primes_indx);
    }
    clock_t end_print = clock();

    ull prime_count = 0;
    for(ull i = 0; i < primes_max; ++i)
    {
        if(primes[i])
        {
            ++prime_count;
        }
    }

    printf("Counted %llu primes\nCalculation took: %0.fms\n",
        prime_count,
        ((double)(end_primes - begin_primes) / CLOCKS_PER_SEC) * (double)1000);

    if(args.printing)
        printf("Printing took %0.fms\n",
            ((double)(end_print  - begin_print ) / CLOCKS_PER_SEC) * (double)1000);

    free(primes);
    return EXIT_SUCCESS;
}

