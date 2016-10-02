/* taocp_1.2.1_P: Equation (1) in Knuth's "The Art of Computer Programming" in section 1.2.1
 * This program is part of the public domain - Kenneth B. Jensen 2016 <kenneth@jensen.cf>
 * Arguments: ./taocp_1.2.1_P [upperlimit]
 * Without the optional argument, the program will print out to 10^2.
 * I've verified that this algorithm is correct up to 1000, with the included script
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint_fast64_t ipow(uint_fast64_t, uint_fast64_t);

int main(int argc, char *argv[]) { 
	char *equation;
	uint_fast64_t i, j;

	if (argc > 1) 
		sscanf(argv[1], "%d", &j);
	else
		j = 10;

	/* see below for declaration reasoning
	   note that for long*/
	equation = (char *)malloc(ipow(j,2)/2);
	memcpy(equation, "1", 1);

	for (i = 1; i <= j; ++i) {
		/* if we use i==1, there will be an extra "+ 1" to the string */
		if (i != 1)
			sprintf(equation, "%s + %d", equation, ipow(i,2)-ipow(i-1,2));

		printf("%s = %d^2\n", equation, i);
	}
	return 0;
}

/* could be procedural, but functional is easier to implement at 3 AM
 * maybe I'll rewrite it for performance later
 * anyways the name and code for it should be self-explanatory,
 * I just didn't want to cast doubles to ints with pow()
 */
uint_fast64_t ipow(uint_fast64_t base, uint_fast64_t exp) {
	if (exp >= 1)
		return base * ipow(base, exp-1);
	return 1;
}
