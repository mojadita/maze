/* maze.c -- Maze module.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Wed Apr 10 16:47:51 EEST 2019
 * Copyright: (C) 2019 Luis Colorado <luiscoloradourcola@gmail.com>
 * 	All rights reserved.
 * License: BSD.
 */

#include <assert.h>
#include <stdlib.h>

#include "mazeP.h"

MAZE
maze_new()
{
	MAZE maze = malloc( sizeof (MAZE) );
	assert( maze != NULL );

	maze->rows = 0;
	maze->cols = 0;
	maze->rows_cell = 0;
	maze->cols_cell = 1;
	maze->to_visit = 0;

	char **cells = NULL;
	return maze;
} /* new_maze */

void
maze_free(MAZE maze)
{
	maze_clear(maze);
	free(maze);
} /* free_maze */

void
maze_init(MAZE maze, int rows, int cols)
{
	maze->rows = rows;
	maze->cols = cols;
	maze->rows_cell = 0;
	maze->cols_cell = 1;
	maze->to_visit = rows * cols;
	maze->cells = malloc( rows * sizeof *maze->cells );
	assert( maze->cells != NULL );
	int r;
	for (r = 0; r < rows; r++) {
		maze->cells[r] = malloc(
			cols * sizeof *maze->cells[r] );
		assert( maze->cells[r] != NULL );
		int c;
		for (c = 0; c < cols; c++)
			maze->cells[r][c] = ALL_WALLS;
	} /* for (r = 0; ... ) */
} /* init_maze */

void
maze_clear(MAZE maze)
{
	if (!maze->cells) return; // nothing to do.
	int r;
	for (r = 0; r < maze->rows; r++)
		free(maze->cells[r]);
	free(maze->cells);
	maze->rows = 0;
	maze->cols = 0;
	maze->rows_cell = 0;
	maze->cols_cell = 1;
	maze->to_visit = 0;
} /* clear_maze */

int
maze_getCols(MAZE maze)
{
	return maze->cols;
} /* maze_getCols */

int
maze_getRows(MAZE maze)
{
	return maze->rows;
} /* maze_getRows */

void
maze_setCellCols(MAZE maze, int cols)
{
	maze->cols_cell = cols;
} /* maze_setCellCols */

void
maze_setCellRows(MAZE maze, int rows)
{
	maze->rows_cell = rows;
} /* maze_setCellRows */

void
maze_setToVisit(MAZE maze, int toVisit)
{
	maze->to_visit = toVisit;
} /* maze_setToVisit */

int
maze_getCellCols(MAZE maze)
{
	return maze->cols_cell;
} /* maze_getCellCols */

int
maze_getCellRows(MAZE maze)
{
	return maze->rows_cell;
} /* maze_getCellRows */

int
maze_getToVisit(MAZE maze)
{
	return maze->to_visit;
} /* maze_getToVisit */

void
maze_setCells(MAZE maze, int row0, int col0,
	int row1, int col1, int val)
{
	assert(    row0 >= 0    && row0 <  maze->rows
		&& row1 >= row0 && row1 <= maze->rows
		&& col0 >= 0    && col0 <  maze->cols
		&& col1 >= col0	&& col1 <= maze->cols);

	int r;
	for (r = row0; r < row1; r++) {
		int c;
		for (c = col0; c < col1; c++)
			maze->cells[r][c] = val;
	}
} /* maze_setCells */

void
maze_setWalls(MAZE maze, int row0, int col0,
			int row1, int col1, int val)
{
	assert(    row0 >= 0    && row0 <  maze->rows
		&& row1 >= row0 && row1 <= maze->rows
		&& col0 >= 0    && col0 <  maze->cols
		&& col1 >= col0	&& col1 <= maze->cols);

	int r;
	for (r = row0; r < row1; r++) {
		int c;
		for (c = col0; c < col1; c++)
			maze->cells[r][c] |= val;
	}
} /* maze_setWalls */

void
maze_resetWalls(MAZE maze, int row0, int col0,
			int row1, int col1, int val)
{
	assert(    row0 >= 0    && row0 <  maze->rows
		&& row1 >= row0 && row1 <= maze->rows
		&& col0 >= 0    && col0 <  maze->cols
		&& col1 >= col0	&& col1 <= maze->cols);

	int r;
	for (r = row0; r < row1; r++) {
		int c;
		for (c = col0; c < col1; c++)
			maze->cells[r][c] &= ~val;
	}
} /* maze_resetWalls */

void
maze_verifyWalls(MAZE maze)
{
	int r;
	for (r = 0; r < maze->rows; r++) {
		int c;
		for (c = 0; c < maze->cols; c++) {
			if (maze->cells[r][c] & VISITED_MARK) {
				if (r > 0 &&
						maze->cells[r-1][c] & VISITED_MARK) {
					maze->cells[r][c]   &= ~NORTH_WALL;
					maze->cells[r-1][c] &= ~SOUTH_WALL;
				}
				if (c < maze->cols-1 &&
						maze->cells[r][c+1] & VISITED_MARK) {
					maze->cells[r][c]   &= ~EAST_WALL;
					maze->cells[r][c+1] &= ~WEST_WALL;
				}
				if (r < maze->rows-1 &&
						maze->cells[r+1][c] & VISITED_MARK) {
					maze->cells[r][c]   &= ~SOUTH_WALL;
					maze->cells[r+1][c] &= ~NORTH_WALL;
				}
				if (c > 0 &&
						maze->cells[r][c-1] & VISITED_MARK) {
					maze->cells[r][c]	&= ~WEST_WALL;
					maze->cells[r][c-1] &= ~EAST_WALL;
				}
			}
		}
	}
} /* maze_verifyWalls */
