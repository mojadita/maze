/* mazeP.h -- private type and constant definitions for MAZE.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Wed Apr 10 15:46:54 EEST 2019
 * Copyright: (C) 2019 Luis Colorado <luiscoloradourcola@gmail.com>
 * 	All rights reserved.
 * License: BSD.
 */
#ifndef _MAZEP_H
#define _MAZEP_H

#include "maze.h"

struct maze {
	char *name;
	int rows, cols;
	int rows_cell, cols_cell;
	int to_visit;
	char **cells;
};

#endif /* _MAZEP_H */
