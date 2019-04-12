/* Name: test_maze.c --test program for the maze.
 * Author: Luis Colorado <luiscoloradourcola@gmail.coms>
 * Date: Thu Apr 11 07:50:13 EEST 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#include <stdio.h>
#include "maze.h"

int main(int argc, char **argv)
{
	MAZE m = maze_new();
	maze_init(m, 20, 20);
#if 0
	maze_setCellCols(m, 3);
	maze_setCellRows(m, 2);
#endif
	maze_setWalls(m, 5, 5, 15, 15, VISITED_MARK);
	maze_verifyWalls(m);
	maze_rdf(m, 0, 0);
	maze_print(m, stdout);
}
