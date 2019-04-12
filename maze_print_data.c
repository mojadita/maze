/* maze_print_data.c -- Maze module printing routine.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Apr 12 08:02:02 EEST 2019
 * Copyright: (C) 2019 Luis Colorado <luiscoloradourcola@gmail.com>
 * 	All rights reserved.
 * License: BSD.
 */

#include <stdlib.h>

#include "mazeP.h"

static char *print_cell(int cell, char *buf, size_t buf_sz)
{
	snprintf(buf, buf_sz, "\"%s%s%s%s%s\"",
		cell & NORTH_WALL ? "N" : "",
		cell & EAST_WALL ? "E" : "",
		cell & SOUTH_WALL ? "S" : "",
		cell & WEST_WALL ? "W" : "",
		cell & VISITED_MARK ? "*" : "");
	return buf;
} /* print_cell */

size_t maze_print_data(MAZE mz, FILE *out)
{
	int row, col;
	size_t res = 0;

	res += fprintf(out, "{");
	for(row = 0; row < mz->rows; row++) {
		if (row) {
			res += fprintf(out, ",\n ");
		}
		fprintf(out, "{");
		for(col = 0; col < mz->cols; col++) {
			char buffer[20];
			res += fprintf(out, "%s%7s",
				col ? ", " : "",
				print_cell(mz->cells[row][col],
					buffer, sizeof buffer));
		}
		fprintf(out, "}");
	} /* for (r ...) */
	res += fprintf(out, "};\n");
	return res;
} /* maze_print */
