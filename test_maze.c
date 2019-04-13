/* Name: test_maze.c -- simple test program for the MAZE.
 * Author: Luis Colorado <luiscoloradourcola@gmail.coms>
 * Date: Thu Apr 11 07:50:13 EEST 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <stdlib.h>

#include "maze.h"

#define F(_fmt) __FILE__":%d:%s: " _fmt, __LINE__, __func__

int main(int argc, char **argv)
{
	int opt;
	int cols = 20, rows = 20, cell_rows = -1, cell_cols = -1;

	while ((opt = getopt(argc, argv, "s:Sp:r:c:R:C:")) >= 0) {
		switch(opt) {
		case 's': {
				int seed = atoi(optarg);
				srandom(seed);
				fprintf(stderr,
					F("seed set to %d\n"),
					seed);
			} /* block */
			break;
		case 'S': {
				struct timespec now;
				clock_gettime(CLOCK_REALTIME_PRECISE, &now);
				int seed = now.tv_sec ^ now.tv_nsec;
				srandom(seed);
				fprintf(stderr,
					F("seed set to %d\n"),
					seed);
			} /* block */
			break;
		case 'p':
			switch(optarg[0]) {
			default:
			case 'u': maze_print = maze_print_utf8; break;
			case '#': maze_print = maze_print_2chars; break;
			case 'a': maze_print = maze_print_simple; break;
			case 'c': maze_print = maze_print_data; break;
			} /* switch */
			break;
		case 'r': rows = atoi(optarg); break;
		case 'c': cols = atoi(optarg); break;
		case 'R': cell_rows = atoi(optarg); break;
		case 'C': cell_cols = atoi(optarg); break;
		} /* switch */
	} /* while */

	MAZE m = maze_new();
	maze_init(m, rows, cols);
	if (cell_rows >= 0) maze_setCellRows(m, cell_rows);
	if (cell_cols >= 0) maze_setCellCols(m, cell_cols);
	maze_rdf(m, 0, 0);
	maze_resetWalls(m, 0, 0, 1, 1, WEST_WALL);
	maze_resetWalls(m, rows-1, cols-1, rows, cols, EAST_WALL);
	maze_print(m, stdout);
}
