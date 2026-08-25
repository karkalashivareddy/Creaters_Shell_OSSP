# Skill-01 Makefile
# OSSP - 25CS2104E

CC = gcc
CFLAGS = -Wall -Wextra
SRCDIR = src
BINDIR = bin

all: $(BINDIR)/fork_demo $(BINDIR)/exec_demo

$(BINDIR)/fork_demo: $(SRCDIR)/fork_demo.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR)/exec_demo: $(SRCDIR)/exec_demo.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

run_fork: $(BINDIR)/fork_demo
	./$(BINDIR)/fork_demo

run_exec: $(BINDIR)/exec_demo
	./$(BINDIR)/exec_demo

run: all run_fork run_exec

clean:
	rm -rf $(BINDIR)

.PHONY: all run_fork run_exec run clean
