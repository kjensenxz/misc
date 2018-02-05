// mango.c v1.0.2 - short program to print out "mango"
// Copyright (C) 2018 joe_dirt plz no steal

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STRBUF 7
// STRBUF[-1] = '\0'

// 'sys' functions -- shell to API
void usage (int argc, char **argv);
void parseopts (int argc, char **argv);

// API functions -- API to ABI
void mango(const char *);
// void mangor(const char *); // 2.0 feature

// ABI functions -- the real workhorses, computational functions
void mangoh(char *);
void mangov(char *);
// void mangorv(char *); // 2.0 feature
// void mangorh(char *); // 2.0 feature

void mangov(char *msg) {
	unsigned char i = 0;
	for (i = 0; i < strnlen(msg, STRBUF); ++i) {
		printf("%c\n", i[msg]);
	}
}

void mangoh(char *msg) {
	// msg is already guaranteed to be alloc'd and in-bounds, just skip all of this,
	// the API mango()
	/*
	if (m == NULL) {
		fprintf(stderr, "Value is a null pointer, terminating with"
				" EXIT_FAILURE.\r\n");
		exit(EXIT_FAILURE);
	}
	*/

	// notes for adapting into taking any value
	// STRBUF == 25; msg[24] = '\0', 23 is len, (25-2) = 23; 23 * 2 includes a space for every char,
	// we only need one: (STRBUF - 2) * 2 - 1 = STRBUF * 2 - 5
	// we still need one more for the '\0': STRBUF * 2 - 4
	// this is true as long as STRBUF >= 2 max input
	// yes, it leaves a single space on odd-length strings
	
	#define STRSPBUF (STRBUF * 2) - 4
	unsigned char i = 0;
	char *msgsp = calloc(sizeof(char *), STRSPBUF);
	for (i = 0; i < STRSPBUF; ++i) {
		msgsp[i] = msg[i/2];
		msgsp[++i] = ' ';
	}

	for (i = 0; i <= STRSPBUF; ++i) {
		printf("%d %x\n", i, msgsp[i]);
	}
	printf("%s\n", msgsp);
	
	return;	
}

void
mango(const char *str) {
	unsigned char i = 0;
	char *m = calloc(sizeof(char *), STRBUF);

	if (m == NULL) {
		fprintf(stderr, "Failed to allocate memory, terminating with"
				" EXIT_FAILURE.\r\n");
		exit(EXIT_FAILURE);
	}

	strncat(m, str, STRBUF-1);

	mangoh(m);

	mangov(m);


	free(m);

	return;
}

int
main (int argc, char **argv) {
	unsigned char i = 0;
	if (argc > 1) {
		parseopts(argc, argv);
	}
	else {
		mango("mango");
	}


	return EXIT_SUCCESS;
}

void
parseopts(int argc, char **argv) {
	int c = 0;
	while ((c = getopt(argc, argv, "h?")) != -1) {
		printf("%d", c)
		switch (c) {
			case 'h':
			case '?':
			default :
				usage(argc, argv);
		}
	}

	return;
}

void
usage(int argc, char **argv) {
	fprintf(stderr,
		"Usage: %s\n",
		argv[0]);
	exit(EXIT_SUCCESS);
}
