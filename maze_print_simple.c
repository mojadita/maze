/* maze_print.c -- Maze module printing routine.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Apr 11 08:09:27 EEST 2019
 * Copyright: (C) 2019 Luis Colorado <luiscoloradourcola@gmail.com>
 * 	All rights reserved.
 * License: BSD.
 */

#include <stdlib.h>

#include "mazeP.h"

static size_t add_first_line(MAZE mz, FILE *out)
{
	int col;
	size_t res = 0;
	fputc(' ', out); res++;
	for (col = 0; col < mz->cols; col++) {
		int n;
		for (n = 0; n < mz->cols_cell; n++)
			fputc(mz->cells[0][col] & NORTH_WALL
					? '_'
					: ' ',
				out);
		fputc(' ', out);
		res += n;
	} /* for (col ...) */
	fputs("\n", out);
	return ++res;
} /* add_first_line */

static size_t add_body_row_line(MAZE mz, FILE *out, int row)
{
	int col;
	fputc(mz->cells[row][0] & WEST_WALL
			? '|'
			: ' ',
		out);
	for (col = 0; col < mz->cols; col++) {
		int n;
		for (n = 0; n < mz->cols_cell; n++)
			fputc(' ', out);
		fputc(mz->cells[row][col] & EAST_WALL
				? '|'
				: ' ',
			out);
	} /* for (col ...) */
	fputs("\n", out);
	return (mz->cols_cell +1) * mz->cols + 1;
} /* add_body_row_line */

static size_t add_inter_row_line(MAZE mz, FILE *out, int row)
{
	int col;
	size_t res = 0;

	fputc(mz->cells[row][0] & WEST_WALL
			? '|'
			: ' ',
		out); res++;
	for (col = 0; col < mz->cols; col++) {
		int n;
		for (n = 0; n < mz->cols_cell; n++)
			fputc(mz->cells[row][col] & SOUTH_WALL
					? '_'
					: ' ',
				out);
		fputc(mz->cells[row][col] & EAST_WALL
				? '|'
				: '.',
			out);
		res += n;
	} /* for (col ...) */
	fputs("\n", out);
	return ++res;
} /* add_inter_row_line */

size_t maze_print(MAZE mz, FILE *out)
{
	int row;
	size_t res = 0;


	add_first_line(mz, out);
	for(row = 0; row < mz->rows; row++) {
		int n;
		for (n = 0; n < mz->rows_cell; n++)
			res += add_body_row_line(mz, out, row);
		res += add_inter_row_line(mz, out, row);
	} /* for (r ...) */
	return res;
} /* maze_print */
