/* maze_print.c -- Maze module printing routine.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Apr 11 08:09:27 EEST 2019
 * Copyright: (C) 2019 Luis Colorado <luiscoloradourcola@gmail.com>
 * 	All rights reserved.
 * License: BSD.
 */

#include <stdlib.h>

#include "mazeP.h"

static int move_north(int arg)
{
	return arg & NORTH_WALL ? SOUTH_WALL : 0;
}

static int move_east(int arg)
{
	return arg & EAST_WALL ? WEST_WALL : 0;
}

static int move_south(int arg)
{
	return arg & SOUTH_WALL ? NORTH_WALL : 0;
}

static int move_west(int arg)
{
	return arg & WEST_WALL ? EAST_WALL : 0;
}

static char *strtable[] = {
	/*         NORTH               NORTH   *
	 *                   EAST      EAST    */
	" ",      "\u2576", "\u2575", "\u2514",
	"\u2574", "\u2500", "\u2518", "\u2534", /* SOUTH */
	"\u2577", "\u250c", "\u2502", "\u251c", /* WEST */
	"\u2510", "\u252c", "\u2524", "\u253c", /* SOUTH & WEST */
};

static size_t add_first_line_first_char(MAZE mz, FILE *out)
{
	fputs(strtable[mz->cells[0][0] & (NORTH_WALL | WEST_WALL)],
		out);
	return 1;
}

static size_t add_inter_col_top_char(MAZE mz, FILE *out,
		int col)
{
	fputs(strtable[move_north(mz->cells[0][col-1])
		| (mz->cells[0][col] & (NORTH_WALL | WEST_WALL))],
		out);
	return 1;
}

static size_t add_cell_body_top_char(MAZE mz, FILE *out,
		int row, int col)
{
	fputs(strtable[move_north(mz->cells[row][col])
		| (mz->cells[row][col] & NORTH_WALL)], out);
	return 1;
}

static size_t add_first_line_last_char(MAZE mz, FILE *out)
{
	fputs(strtable[move_north(mz->cells[0][mz->cols-1])
		| move_east(mz->cells[0][mz->cols-1])], out);
	return 1;
}

static size_t add_inter_row_first_char(MAZE mz, FILE *out,
		int row)
{
	fputs(strtable[move_west(mz->cells[row-1][0])
		| (mz->cells[row][0] & (NORTH_WALL | WEST_WALL))], out);
	return 1;
}

static size_t add_inter_row_inter_cell_char(MAZE mz, FILE *out,
		int row, int col)
{
	fputs(strtable[
		  (mz->cells[row-1][col-1] & (SOUTH_WALL | EAST_WALL))
		| (mz->cells[row][col]     & (NORTH_WALL | WEST_WALL))],
		out);
	return 1;
}

static size_t add_inter_row_last_cell_char(MAZE mz, FILE *out,
		int row)
{
	fputs(strtable[move_east(mz->cells[row][mz->cols-1])
		| (mz->cells[row-1][mz->cols-1] & (SOUTH_WALL | EAST_WALL))],
		out);
	return 1;
}

static size_t add_body_row_inter_cell_left_char(MAZE mz, FILE *out,
		int row, int col)
{
	fputs(strtable[move_west(mz->cells[row][col])
		| (mz->cells[row][col] & WEST_WALL)],
		out);
	return 1;
}

static size_t add_cell_body_char(MAZE mz, FILE *out)
{
	fputs(strtable[0], out);
	return 1;
}

static size_t add_cell_body_last_char(MAZE mz, FILE *out,
		int row)
{
	fputs(strtable[move_east(mz->cells[row][mz->cols-1])
		| (mz->cells[row][mz->cols-1] & EAST_WALL)],
		out);
	return 1;
}

static size_t add_last_line_first_char(MAZE mz, FILE *out)
{
	fputs(strtable[
		  move_south(mz->cells[mz->rows-1][0])
		| move_west( mz->cells[mz->rows-1][0])],
		out);
	return 1;
}

static size_t add_last_line_inter_cell_char(MAZE mz, FILE *out,
		int col)
{
	fputs(strtable[
		  move_south(mz->cells[mz->rows-1][col])
		| (mz->cells[mz->rows-1][col-1] & (SOUTH_WALL|EAST_WALL))],
		out);
	return 1;
}

static size_t add_cell_body_bottom_char(MAZE mz, FILE *out,
		int col)
{
	fputs(strtable[
		  move_south(mz->cells[mz->rows-1][col])
		| (mz->cells[mz->rows-1][col] & SOUTH_WALL)],
		out);
	return 1;
}

static size_t add_last_line_last_char(MAZE mz, FILE *out)
{
	fputs(strtable[
		  mz->cells[mz->rows-1][mz->cols-1]
		& (SOUTH_WALL | EAST_WALL)],
		out);
	return 1;
}

static size_t add_first_line(MAZE mz, FILE *out)
{
	int col;
	size_t res = 0;
	for (col = 0; col < mz->cols; col++) {
		if (!col)
			res += add_first_line_first_char(mz, out);
		else
			res += add_inter_col_top_char(mz, out, col);
		int n;
		for (n = 0; n < mz->cols_cell; n++)
			res += add_cell_body_top_char(mz, out, 0, col);
	} /* for (col ...) */
	res += add_first_line_last_char(mz, out);
	fputc('\n', out);
	return ++res;
} /* add_first_line */

static size_t add_inter_row_line(MAZE mz, FILE *out, int row)
{
	int col;
	size_t res = 0;
	for (col = 0; col < mz->cols; col++) {
		if (!col)
			res += add_inter_row_first_char(mz, out, row);
		else
			res += add_inter_row_inter_cell_char(mz, out, row, col);
		int n;
		for (n = 0; n < mz->cols_cell; n++)
			res += add_cell_body_top_char(mz, out, row, col);
	} /* for (col ...) */
	res += add_inter_row_last_cell_char(mz, out, row);
	fputc('\n', out);
	return ++res;
} /* add_inter_row_line */

static size_t add_body_row_line(MAZE mz, FILE *out, int row)
{
	int col;
	size_t res = 0;
	for (col = 0; col < mz->cols; col++) {
		res += add_body_row_inter_cell_left_char(mz, out, row, col);
		int n;
		for (n = 0; n < mz->cols_cell; n++)
			res += add_cell_body_char(mz, out);
	} /* for (col ...) */
	res += add_cell_body_last_char(mz, out, row);
	fputc('\n', out);
	return ++res;
} /* add_body_row_line */

static size_t add_last_line(MAZE mz, FILE *out)
{
	int col;
	size_t res = 0;
	for (col = 0; col < mz->cols; col++) {
		if (!col)
			res += add_last_line_first_char(mz, out);
		else
			res += add_last_line_inter_cell_char(mz, out, col);
		int n;
		for (n = 0; n < mz->cols_cell; n++)
			res += add_cell_body_bottom_char(mz, out, col);
	} /* for (col ...) */
	res += add_last_line_last_char(mz, out);
	fputc('\n', out);
	return ++res;
} /* add_last_line */

size_t maze_print(MAZE mz, FILE *out)
{
	int row;
	size_t res = 0;

	for(row = 0; row < mz->rows; row++) {
		if (!row)
			res += add_first_line(mz, out);
		else
			res += add_inter_row_line(mz, out, row);
		int n;
		for (n = 0; n < mz->rows_cell; n++)
			res += add_body_row_line(mz, out, row);
	} /* for (r ...) */
	return res + add_last_line(mz, out);
} /* maze_print */
