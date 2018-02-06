// mango.c v1.1.2 - mango your text!
// Copyright (C) 2018 joe_dirt plz no steal

// TODO: errno.h
// TODO: v2.0: reverse mango!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 'sys' functions -- shell to API
void usage (int, char **);
void parseopts (int, char **, const char *);
const char * argvtostr (int, char **);

// API functions -- API to ABI (to be moved to a library)
void mango(const char *);
void mangor(const char *x) {}; // 2.0 feature

// ABI functions -- the real workhorses, computational functions (also to be moved to a library)
void mangoh(const char *);
void mangov(const char *);
void mangorv(const char *); // 2.0 feature
void mangorh(const char *); // 2.0 feature

void mangov(const char *msg) {
        unsigned char i = 0;
        for (i = 1; i < strlen(msg) - 1 ; ++i) {
                // the first and last char can be safely skipped to format output correctly
                printf("%c\n", i[msg]);
        }
}

void mangoh(const char *msg) {
	unsigned char i = 0;
        // notes
        // strlen(msg) == msglen (includes '\0')
        // (msglen) * 2 == msglen': another NUL, and a space for every char, including '\0'
        // subtract 3 to remove both NULs, and one's space
        // note this breaks using regular %s formats, but this works in this scenario
        // this will probably need to be revised for v2+
        int buflen = (strlen(msg) * 2) - 3;
        
        char *msgsp = calloc(sizeof(char *), buflen);
	
        for (i = 0; i < buflen; ++i) {
                msgsp[i] = msg[i/2];
                msgsp[++i] = ' ';
        }
	
        printf("%s\n", msgsp);

        free(msgsp);
	
        return;
}

void
mango(const char *str) {
        mangoh(str);
        mangov(str);
        return;
}

int
main (int argc, char **argv) {
        unsigned char i = 0;
	const char *msg = NULL;
	
        parseopts(argc, argv, msg);

        return EXIT_SUCCESS;
}

void
parseopts(int argc, char **argv, const char *msg) {
        unsigned char rflag = 0;
        int c = 0;
        int i = 0, j = 0;

        while ((c = getopt(argc, argv, "h?")) != -1) {
                switch (c) {
                        case 'h':
                        case '?':
                        default :
                                usage(argc, argv);
                                break;
                        case 'r':
                                rflag = 1;

                                break;
                }
        }

        c = 0;

        msg = argvtostr(argc, argv);
        mango(msg);
        free((char *) msg);
}

const char *
argvtostr (int argc, char **argv) {
        int i = 0, j = 0;
        int c = 0;
        char *msg = NULL;
        // find length of argv, add spaces between values, see below
        // TODODONE: these for loops into a argv2str(), this function is becoming a 'god object'
        // TODO: make parseopts a helper, make main() do a litle bit of lifting
        for (i = 1; i < argc; ++i) {
                for (j = 0; j < strlen(argv[i]); ++j) {
                        c++; // characters
                }
                c++; // spaces
        }

        msg = calloc(sizeof(char *), c + 1);

        c = 0;

        for (i = 1; i < argc; ++i) {
                for (j = 0; j < strlen(argv[i]); ++j) {
                        msg[c++] = argv[i][j];
                }
                msg[c++] = ' ';
        }

        return (const char*) msg;
}


void
usage(int argc, char **argv) {
        fprintf(stderr,
                "Usage: %s [your message with as many spaces as you want]\r\n"
                "Mango your text!\r\n"
                "\t -h, -?: This message!\r\n"
                "\t     -v: Version & license information\r\n"
                "\t     -r: Reverse mango!\r\n",
                argv[0]);
        exit(EXIT_SUCCESS);
}
