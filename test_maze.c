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
#if 1
	maze_setCellCols(m, 3);
	maze_setCellRows(m, 1);
#endif
	maze_print(m, stdout);
}