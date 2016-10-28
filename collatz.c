/* collatz.c - Steps required to reach 1 following the Collatz conjecture
 * Public domain -  2016 Kenneth B. Jensen <kenneth@jensen.cf>
 */
#include <stdio.h>

/* I am so sorry for this 
 * Note that values must be small enough to fit 3 * MAX + 1 in the data type
 * There must be a better way
 */
#define TYPE 0 // 0 - char, 1 - short, 2 - long, 3 - long long

#if TYPE == 0
#define MAX_VAL 85
#define DATATYPE char
#elif TYPE == 1
#define MAX_VAL 21844
#define DATATYPE short
#elif TYPE == 2
#define MAX_VAL 141655764
#define DATATYPE long int
#elif TYPE == 3
#define MAX_VAL 6148914691236517204L 
#define DATATYPE long long int
#endif

/* Arguments: None.
 * Output: number[0,MAX_VAL] steps taken
 */
int main (void) {
	unsigned DATATYPE num, cur;
	unsigned short steps; // a short should fit all the steps needed
	printf("number\tsteps\n");

	for (num = 0; num < MAX_VAL; ++num) {
		cur = num; // we do not want to lose num's value; clone it.
		steps = 0;
		printf("%d\t", num);
		while (cur > 1 && ++steps < 65536) {
			cur = (cur & 1) ? cur * 3 + 1 : cur / 2;
		}
		printf("%d\n", steps);
	}
	return 0;
}
