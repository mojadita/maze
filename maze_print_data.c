/* maze_print_data.c -- Maze module printing routine.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Apr 12 08:02:02 EEST 2019
 * Copyright: (C) 2019 Luis Colorado <luiscoloradourcola@gmail.com>
 * 	All rights reserved.
 * License: BSD.
 */

#include <stdlib.h>

#include "mazeP.h"

#define COLS_PER_LINE_MASK 0x03
#define ROWS_PER_LINE_MASK 0x07

static struct bit_desc {
	char *name;
	int	  mask;
} bit_descs[] = {
#define MASK(_arg) { .name = #_arg, .mask = _arg }
	MASK(NORTH_WALL),
	MASK(EAST_WALL),
	MASK(SOUTH_WALL),
	MASK(WEST_WALL),
	MASK(VISITED_MARK),
#undef MASK
	{ .name = NULL, .mask = 0 }
};

static char *cell2string(int cell, char *buf, size_t buf_sz)
{
	size_t n;
	struct bit_desc *bit;
	char *output = buf;
	for (bit = bit_descs; bit->name; bit++) {
		if (cell & bit->mask) {
			if (buf > output) {
				n = snprintf( buf, buf_sz, "|");
				buf += n; buf_sz -= n;
			}
			n = snprintf( buf, buf_sz,
				"%s", bit->name);
			buf += n; buf_sz -= n;
		}
	}
	return output;
} /* print_cell */

#define CELL_FMT "%s_row%d"

size_t maze_print_data(MAZE mz, FILE *out)
{
	int row, col;
	size_t res = 0;

	for(row = 0; row < mz->rows; row++) {
		res += fprintf(out,
			"char *" CELL_FMT "[%d] = {",
			mz->name, row, mz->cols);
		for(col = 0; col < mz->cols; col++) {
			char buffer[128];
			res += fprintf(out, "%s%s",
				col
					?  col & COLS_PER_LINE_MASK
						? ", "
						: ",\n\t\t"
					: "",
				cell2string(mz->cells[row][col],
					buffer, sizeof buffer));
		}
		fprintf(out, "};\n\n");
	} /* for (r ...) */
	res += fprintf(out,
		"char *%s_cells[%d] = {",
		mz->name, mz->rows);
	for (row = 0; row < mz->rows; row++) {
		res += fprintf(out,
			"%s" CELL_FMT,
			row
				? row & ROWS_PER_LINE_MASK
					? ", "
					: ",\n\t\t"
				:"",
			mz->name, row);
	}
	res += fprintf(out, "};\n");
	return res;
} /* maze_print_data */
