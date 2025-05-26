CC = gcc
CFLAGS = -Wall -Wextra -pedantic -v
SRCDIR = src
OBJDIR = obj
BINDIR = bin
INSTALLDIR = /usr/local/bin

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
TARGETS = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%, $(SRCS))

all: prepare $(TARGETS)

$(BINDIR)/%: $(OBJDIR)/%.o | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -pv $(OBJDIR)

$(BINDIR):
	mkdir -pv $(BINDIR)

prepare: | $(OBJDIR) $(BINDIR)

install: all
	install -d $(INSTALLDIR)
	install -m 755 $(TARGETS) $(INSTALLDIR)

clean:
	@rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all prepare clean install
