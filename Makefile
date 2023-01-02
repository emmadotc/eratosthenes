CC    = gcc

FILES = main.c args.c eratosthenes.c common.c
WARNS = -Wall -Wextra -Wpedantic -Wconversion -Wvla
OPTIM = -O3

default:
	$(CC) -std=c99 -march=native -g0 $(OPTIM) $(WARNS) $(FILES) -o primes

debug:
	$(CC) -std=c99 -march=native -g3 $(WARNS) $(FILES) -o primes

clean:
	rm ./primes*

bear:
	make clean ; bear -- make
