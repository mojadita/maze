# Name: Makefile -- makefile for the test program maze.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Thu Apr 11 07:53:08 EEST 2019
# Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
# License: BSD.

targets = maze_utf8 maze_simple maze_2chars
RM ?= rm -f


all: $(targets)
clean:
	$(RM) $(toclean)
distclean: clean
	$(RM) .depend
.depend: Makefile *.c
	mkdep *.c

.PHONY: all clean

common_objs = maze.o test_maze.o maze_rdf.o
maze_utf8_objs = $(common_objs) maze_print_utf8.o
maze_simple_objs = $(common_objs) maze_print_simple.o
maze_2chars_objs = $(common_objs) maze_print_2chars.o

.for t in $(targets)
toclean += $t $($t_objs)
$t: $($t_objs) $($t_deps)
	$(CC) $(LDFLAGS) $($t_ldflags) $($t_objs) $($t_libs) -o $@
.endfor
