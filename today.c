/* today.c - Display current day of week based on date
 * Public domain - 2016 Kenneth B. Jensen <kenneth@jensen.cf>
 * Compile me with -lm
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void) {
	const char *days[7] = {"Saturday", "Sunday", "Monday", "Tuesday", \
		"Wednesday", "Thursday", "Friday"};
	time_t now = time(NULL); 
	char buffer[1024] = {0};

	/* Zeller's congurence
	 * -------------------
	 * h: day of week (see above array)
	 * q: day of month
	 * m: month
	 * k: year of century (year % 100)
	 * j: zero-based century (floor(year / 100))
	 */

	int h, q, m, k, j;

	strftime(buffer, 100, "%d %m %Y", localtime(&now));
	sscanf(buffer, "%d %d %d", &q, &m, &k);

	j = k / 100;
	k %= 100;

	h = (q + (int)floor(13 * (m + 1) / 5) + k + (int)floor(k/4) + (int)floor(j/4) - (2 * j)) % 7;

	printf("Today is %s %d%d-%d-%d.\n", days[h], j, k, m, q);
}
