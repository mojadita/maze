/* maze_print_2chars.c -- Maze module printing routine.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Thu Apr 11 08:09:27 EEST 2019
 * Copyright: (C) 2019 Luis Colorado <luiscoloradourcola@gmail.com>
 * 	All rights reserved.
 * License: BSD.
 */

#include <stdlib.h>
#include <string.h>

#include "mazeP.h"

char filled[] = "##################";
char blank[]  = "                  ";

static void fill(char *what, int n, FILE *out)
{
	int l;
	for (l = strlen(what); n > l; n -= l)
		fputs(what, out);
	fprintf(out, "%.*s", n, what);
}

static void add_first_line(MAZE mz, FILE *out)
{
	int col;

	fputc(filled[0], out);
	for (col = 0; col < mz->cols; col++) {
		fill(mz->cells[0][col] & NORTH_WALL
			? filled : blank,
			mz->cols_cell,
			out);
		fputc(filled[0], out);
	} /* for (col ...) */
	fputc('\n', out);
} /* add_first_line */

static void add_body_row_line(MAZE mz, FILE *out, int row)
{
	int col;

	fputc(mz->cells[row][0] & WEST_WALL
		? filled[0] : blank[0], out);
	for (col = 0; col < mz->cols; col++) {
		fill(blank, mz->cols_cell, out);
		fputc(mz->cells[row][col] & EAST_WALL
				? filled[0] : blank[0],
			out);
	} /* for (col ...) */
	fputc('\n', out);
} /* add_body_row_line */

static void add_inter_row_line(MAZE mz, FILE *out, int row)
{
	int col;

	fputc(filled[0], out);
	for (col = 0; col < mz->cols; col++) {
		fill(mz->cells[row][col] & SOUTH_WALL
				? filled : blank,
			mz->cols_cell, out);
		fputc(filled[0], out);
	} /* for (col ...) */
	fputs("\n", out);
} /* add_inter_row_line */

size_t maze_print_2chars(MAZE mz, FILE *out)
{
	int row;

	if (mz->rows_cell < 1) mz->rows_cell = 1;
	if (mz->cols_cell < 1) mz->cols_cell = 1;
	add_first_line(mz, out);
	for(row = 0; row < mz->rows; row++) {
		int n;
		for (n = 0; n < mz->rows_cell; n++)
			add_body_row_line(mz, out, row);
		add_inter_row_line(mz, out, row);
	} /* for (r ...) */
	return (mz->rows+2)*(mz->cols+3);
} /* maze_print_2chars */
