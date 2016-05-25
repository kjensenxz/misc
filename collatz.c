/* collatz.c - Steps required to reach 1 following the Collatz conjecture from 0 to 2^64-1
 * Copyright (C) 2016 Kenneth B. Jensen <kenneth@jensen.cf>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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


int main (void) {
	unsigned DATATYPE num, cur;
	unsigned short steps; // a short should fit all the steps needed
	printf("number\tsteps\n");

	for (num = 0; num < MAX_VAL; ++num) {
		cur = num; 
		steps = 0;
		printf("%d\t", num);
		while (cur > 1 && ++steps < 65536) {
			cur = (cur & 1) ? cur * 3 + 1 : cur / 2;
		}
		printf("%d\n", steps);
	}
	return 0;
}
