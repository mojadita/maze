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
#if 0
	/* set inner part as nonvisited */
	maze_setWalls(m, rows/4, cols/4, 3*rows/4, 3*cols/4, VISITED_MARK);
	/* make a rectangle in the middle */
	maze_rdf(m, 0, 0);
	maze_switchWalls(m, rows/4, cols/4, 3*rows/4, 3*cols/4, VISITED_MARK);
	maze_setWalls(m, rows/2 - 2, cols/2 - 2, rows/2 + 2, cols/2 + 2,
		VISITED_MARK);
#endif
	maze_rdf(m, rows/4, cols/4);
#if 0
	maze_resetWalls(m, 0, 0, rows, cols, VISITED_MARK);
	maze_setWalls(m,
		rows/2 - 2, cols/2 - 2,
		rows/2 + 2, cols/2 + 2,
		VISITED_MARK);
	maze_setWalls(m,
		rows/2 - 2, cols/2 - 3,
		rows/2 - 1, cols/2 - 1,
		VISITED_MARK);
	maze_setWalls(m,
		3*rows/4 - 1, 3*cols/4 - 1,
		3*rows/4, 3*cols/4 + 1,
		VISITED_MARK);
	maze_verifyWalls(m);
	maze_resetWalls(m,
		0, 0, 1, 1,
		WEST_WALL);
#endif
	maze_resetWalls(m, 0, 0, 1, 1, NORTH_WALL | WEST_WALL);
	maze_resetWalls(m, rows-1, cols-1, rows, cols, EAST_WALL | SOUTH_WALL);
	maze_print(m, stdout);
}
