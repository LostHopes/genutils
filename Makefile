CC=gcc
BINDIR=bin
CFLAGS=-Wall -Wextra -pedantic

all: build
	$(CC) $(CFLAGS) src/lsg.c -o $(BINDIR)/lsg
	$(CC) $(CFLAGS) src/cpg.c -o $(BINDIR)/cpg

build:
	mkdir -pv $(BINDIR)

install:


clean:
	rm -r $(BINDIR)

run:
	./$(BINDIR)/$(BINARY)


check:
