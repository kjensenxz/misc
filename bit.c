#include <stdio.h>
#include <stdint.h>

int main(void) { 
	uint32_t values = 0;
	uint8_t i = 0; 
	/* who says we need two vars for two counters? 
	 * 0 1 2 3 4 | 5 6 7
	 *  forloop  | value
	 */
	for (i = 0; i >> 3 < 16; i += 1 << 3) {
		values |= (i & 0x07) << ((i >> 3) << 1);
		i = (i & 0x07) < 3 ? i+1 : i & 0xF8;
	}

	// we no longer need i to be packed
	for (i = 0; i < 16; ++i) {
		printf("%d\n", (values & (3 << (i << 1))) >> (i << 1));
	}
	return 0;
}
