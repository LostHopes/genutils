CC=gcc
BINDIR=bin
CFLAGS=-Wall -Wextra -pedantic

all: build
	$(CC) $(CFLAGS) src/lsg.c -o $(BINDIR)/lsg

release: build
	$(CC) $(CFLAGS) -o2 src/lsg.c -o $(BINDIR)/lsg

build:
	mkdir -pv $(BINDIR)

install:


clean:
	rm -r $(BINDIR)

run:
	./$(BINDIR)/lsg


check: