CC=gcc
BINDIR=bin

all: build
	$(CC) src/lsg.c -o $(BINDIR)/lsg
	$(CC) src/cpg.c -o $(BINDIR)/cpg

build:
	mkdir -pv $(BINDIR)

clean:
	rm -r $(BINDIR)

run:
	./$(BINDIR)/$(BINARY)
