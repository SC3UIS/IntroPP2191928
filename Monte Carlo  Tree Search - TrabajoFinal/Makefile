# Compiler settings - Can be customized.
CC = gcc
CFLAGS = -Wall -fopenmp
LDFLAGS = -lm

# Makefile settings - Can be customized.
APPNAME = MCTS_OpenMP
EXT = .c
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*$(EXT))
OBJECTS = $(SOURCES:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)

all: $(BINDIR)/$(APPNAME)

$(BINDIR)/$(APPNAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*$(EXT) $(BINDIR)/$(APPNAME)

.PHONY: all clean
