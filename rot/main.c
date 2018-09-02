#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdnoreturn.h>
#include "rot.h"

static void parseopts(int, char **, int *);
static const char *argvtostr(int, char **);
static void usage(int, char**);
static void version(void);


int
main(int argc, char **argv) {
	int rotval = 13;
	const char *msg = NULL;
	const char *rotmsg = NULL;

	parseopts(argc, argv, &rotval);

	msg = argvtostr(argc, argv);

	if (msg == NULL) {
		usage(argc, argv);
	}

	rotmsg = rot(rotval, msg);
	if (rotmsg != NULL) {
		printf("%s\n", rotmsg);
	}

	return EXIT_SUCCESS;
}

static void
parseopts(int argc, char **argv, int *rotval) {
	int c = 0;

	while ((c = getopt(argc, argv, "vr:h?")) != -1) {
		switch(c) {
			case 'v':
				version();
				break;
			case 'r':
				*rotval = atoi(optarg);
				break;
			case 'h':
			case '?':
			default :
				usage(argc, argv);
				break;
		}
	}
}

static const char *
argvtostr(int argc, char **argv) {
	int i, j, k = 0;
	int ct = 0;
	char *msg = NULL;

	for (i = optind; i < argc; ++i) {
		for (j = 0; j < strlen(argv[i]); ++j) {
			ct++;
		}
	}

	msg = calloc(sizeof(char *), ct);

	for (i = optind, k = 0; i < argc; ++i) {
		for (j = 0; j < strlen(argv[i]); ++j, ++k) {
			msg[k] = argv[i][j];
		}
		msg[k++] = ' ';
	}
	msg[k-1] = '\0';

	if (strlen(msg) < 1) {
		return NULL;
	}

	return (const char *) msg;
}

noreturn static void
usage(int argc, char **argv) {
	fprintf(stderr,
		"Usage: %s [-r int] your message here\r\n"
		"Rot-cipher your text! Default is rot13.\r\n"
		"\t -h, -?: This message!\r\n"
		"\t     -v: Version & license information\r\n"
		"\t     -r: Radix for rot (mod 26)\r\n",
		argv[0]);
	exit(EXIT_SUCCESS);
}

noreturn static void
version(void) {
	fprintf(stderr, "rot - Copyright (C) 2018 Kenneth B. Jensen\r\n"
		"This is free and unencumbered software released into the public domain.\r\n"
	);
	exit(EXIT_SUCCESS);
}
