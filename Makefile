# Name: Makefile -- makefile for the test program maze.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Thu Apr 11 07:53:08 EEST 2019
# Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
# License: BSD.

targets = maze
toclean = $(targets)
RM ?= rm -f
INSTALL ?= install
prefix ?= $(HOME)
bindir ?= $(prefix)/bin
mandir ?= $(prefix)/man/man6

all: $(targets)
clean:
	$(RM) $(toclean)
distclean: clean
	$(RM) .depend
.depend: Makefile *.c
	mkdep *.c
install:
	$(INSTALL) maze $(bindir)
	$(INSTALL) maze.6 $(mandir)

.PHONY: all clean

maze_objs = test_maze.o maze.o maze_print_utf8.o \
	maze_print_2chars.o maze_print_simple.o \
	maze_print_data.o maze_rdf.o
toclean += $(maze_objs)

maze: $(maze_objs) $(maze_deps)
	$(CC) $(LDFLAGS) $(maze_ldflags) $(maze_objs) $(maze_libs) -o $@
