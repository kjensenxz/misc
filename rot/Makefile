.SUFFIXES: .c .o

PREFIX = /usr/local

CC = gcc

CFLAGS  = --std=gnu11 -Wall -Werror -Wpedantic -O2
LDFLAGS =

SRC = main.c rot.c
OBJ = $(SRC:.c=.o)
INC = rot.h
BIN = rot

all: options $(BIN)

options:
	@echo "BINARY  = $(BIN)"
	@echo "CFLAGS  = $(CFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "CC      = $(CC)"
	@echo "PREFIX  = $(PREFIX)"

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)
	strip -s $@

clean:
	rm -f $(BIN) $(OBJ)

install: all
	mkdir -p $(PREFIX)/bin/
	cp -f $(BIN) $(PREFIX)/bin/
	chmod 755 $(PREFIX)/bin/$(BIN)

uninstall:
	rm -f $(PREFIX)/bin/$(BIN)

.PHONY: all
