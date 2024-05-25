/* maze.h -- constant ant type definitions for MAZE object.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Wed Apr 10 16:14:22 EEST 2019
 * Copyright: (C) 2019 Luis Colorado <luiscoloradourcola@gmail.com>
 * 	All rights reserved.
 * License: BSD.
 */
#ifndef _MAZE_H
#define _MAZE_H

#include <stdio.h>

#define NORTH_WALL		(1 << 0)
#define EAST_WALL		(1 << 1)
#define SOUTH_WALL		(1 << 2)
#define WEST_WALL		(1 << 3)

#define VISITED_MARK	(1 << 4)

#define ALL_WALLS	(NORTH_WALL | EAST_WALL | SOUTH_WALL |\
						WEST_WALL)

typedef struct maze *MAZE; /* opaque */

MAZE	maze_new();

void	maze_free(MAZE maze);

void	maze_init(MAZE maze, int rows, int cols);

void	maze_clear(MAZE maze);

char *maze_getName(MAZE maze);

int	maze_getCols(MAZE maze);

int	maze_getRows(MAZE maze);

void maze_setName(MAZE maze, char *name);

void	maze_setCellCols(MAZE maze, int cols);

void	maze_setCellRows(MAZE maze, int rows);

void 	maze_setToVisit(MAZE maze, int toVisit);

int	maze_getCellCols(MAZE maze);

int	maze_getCellRows(MAZE maze);

int	maze_getToVisit(MAZE maze);

void	maze_setCells(MAZE maze, int row0, int col0,
			int row1, int col1, int val);

void	maze_setWalls(MAZE maze, int row0, int col0,
			int row1, int col1, int val);

void	maze_resetWalls(MAZE maze, int row0, int col0,
			int row1, int col1, int val);

void	maze_switchWalls(MAZE maze, int row0, int col0,
			int row1, int col1, int val);

void	maze_verifyWalls(MAZE maze);

extern size_t	(*maze_print)(MAZE maze, FILE *out);

size_t maze_print_simple(MAZE maze, FILE *out);
size_t maze_print_utf8(MAZE maze, FILE *out);
size_t maze_print_data(MAZE maze, FILE *out);
size_t maze_print_2chars(MAZE maze, FILE *out);

void maze_rdf(MAZE mz, int row, int col);

#endif /* _MAZE_H */
