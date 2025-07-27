# Name: Makefile -- makefile for the test program maze.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Thu Apr 11 07:53:08 EEST 2019
# Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
# License: BSD.

targets      = maze
toclean      = $(targets)

RM          ?= rm -f
INSTALL     ?= install
GZIP        ?= gzip -v
prefix      ?= /usr/local
bindir      ?= $(prefix)/bin
datarootdir ?= $(prefix)/share
mandir      ?= $(prefix)/share/man
man6dir     ?= $(mandir)/man6

all: $(targets)
clean:
	$(RM) $(toclean)
distclean: clean
	$(RM) .depend

.depend: Makefile *.c
	mkdep *.c

toinstall = $(bindir)/maze $(man6dir)/maze.6.gz
install: $(toinstall)

$(bindir)/maze: maze $(bindir)
	$(INSTALL) maze $(bindir)

$(man6dir)/maze.6.gz: maze.6.gz $(man6dir)
	$(INSTALL) maze.6 $(man6dir)

$(bindir) $(man6dir):
	$(INSTALL) -d $@

.SUFFIXES: .6.gz .6

.6.6.gz:
	$(GZIP) < $<  > $@

.PHONY: all clean

maze_objs = test_maze.o maze.o maze_print_utf8.o \
	maze_print_2chars.o maze_print_simple.o \
	maze_print_data.o maze_rdf.o
toclean += $(maze_objs)

maze: $(maze_objs) $(maze_deps)
	$(CC) $(LDFLAGS) $(maze_ldflags) $(maze_objs) $(maze_libs) -o $@
