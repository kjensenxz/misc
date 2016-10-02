/* why is this a thing again? */
#include <stdio.h>
#include <stdint.h>

int main(void) {
	uint8_t i;
	for (i = 1; i < 101; ++i) {
		if (!(i % 15))
			printf("fizzbuzz");
		else if (!(i % 3))
			printf("fizz");
		else if (!(i % 5))
			printf("buzz");
		else printf("%d", i);
		putchar('\n');
	}
}

