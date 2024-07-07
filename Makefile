CC=gcc
BINDIR=bin
BINARY=genutils
FILES=$(shell find . -name "*.c")

all: build
	$(CC) $(FILES) -o $(BINDIR)/$(BINARY)

build:
	mkdir -pv $(BINDIR)

clean:
	rm -r $(BINDIR)/$(BINARY)

run:
	./$(BINDIR)/$(BINARY)
