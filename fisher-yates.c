#include <stdio.h>
#include <stdlib.h>
/* using time() isn't good enough since it only returns seconds
 * also gettimeofday() may be removed; see man 3 gettimeofday
 */
#include <sys/timeb.h> 

int main() {
	uint_fast8_t x[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	uint_fast8_t i, j;
	struct timeb *tp;

	ftime(tp);
	srand(tp->millitm);

	for (i = 9; i > 0; --i) {
		uint_fast8_t q;
		j = rand() % 10;
		if (x[i] == x[j]) continue; // xor-swapping same values zeroes it out; also is a waste of (precious) cpu cycles
		x[i] ^= x[j];
		x[j] ^= x[i];
		x[i] ^= x[j];
	}
	for (i = 0; i < 10; ++i) {
		printf("%d\n", x[i]);
	}
}

