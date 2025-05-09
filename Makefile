CC = gcc
CFLAGS = -Wall -Wextra -pedantic -v
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGETS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%, $(SRCS))

all: prepare $(TARGETS)

$(BINDIR)/%: $(OBJDIR)/%.o
	$(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

prepare:
	mkdir -pv $(OBJDIR) $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)


.PHONY: all prepare clean