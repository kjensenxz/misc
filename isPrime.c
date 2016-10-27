/* isPrime.c - efficient prime-checking algorithm using bitmasks
 * This program is part of the public domain - Kenneth B. Jensen 2016 <kenneth@jensen.cf>
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Note that using a negative integer here will result in errors
 * For that to work, this algorithm would need to be altered slightly
 * Shouldn't be too hard, but I have had no use case for negative primes (yet)
 */
int isPrime(uint32_t n) {
        // I don't actually remember how I derived this
	uint32_t mask = n >> 31;
	n = (mask ^ n) - mask;

	if (n < 4) return 1 % n; // 1 is not a prime number; 1 % 1 == 0, this also cuts down on a cmp operation for n == 1
	if (!(n & 1)) return 0;

	uint32_t i;

        // All even numbers have already been eliminated with the (n & 1) check; no need to check them
	for (i = 3; i <= sqrtl((long double)n) + 1; i += 2) {
		if (n % i == 0) return 0;
	}
	return 1;
}


void main() {
	int i;
	for (i = -100; i <= 100; ++i) {
		printf("%d %d\n", i, isPrime(i));
        }
}
