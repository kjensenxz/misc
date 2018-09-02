#include <string.h>
#include <ctype.h>
#include "rot.h"

#define ALPHA_LEN 26

char *
rot(int radix, const char *str) {
	char *rot, *p, c;

	if (str == NULL) {
		return NULL;
	}

	radix %= ALPHA_LEN;
	rot = strdup(str);

	if (rot == NULL) {
		return NULL;
	}

	for (p = rot; p < rot + strlen(rot); ++p) {
		if (!isalpha(*p)) {
			continue;
		}

		c = toupper(*p);
		*p += (c <= 'Z' - radix) ? radix : -ALPHA_LEN + radix;
	}

	return rot;
}

inline char *
rot13(const char *str) {
	return rot(13, str);
}
