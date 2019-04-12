/* Name: maze_rdf.c --random depth first recursive algorithm.
 * Author: Luis Colorado <luiscoloradourcola@gmail.coms>
 * Date: Thu Apr 11 07:50:13 EEST 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <stdlib.h>

#include "mazeP.h"

static void
maze_rdf_north(MAZE mz, int row, int col)
{
	if (row - 1 < 0
			|| mz->cells[row - 1][col]
				& VISITED_MARK)
		return;
	mz->cells[row--][col] &= ~NORTH_WALL;
	mz->cells[row][col]   &= ~SOUTH_WALL;
	maze_rdf(mz, row, col);
} /* maze_rdf_north */

static void
maze_rdf_east(MAZE mz, int row, int col)
{
	if (col + 1 >= mz->cols
			|| mz->cells[row][col + 1]
				& VISITED_MARK)
		return;
	mz->cells[row][col++] &= ~EAST_WALL;
	mz->cells[row][col]   &= ~WEST_WALL;
	maze_rdf(mz, row, col);
} /* maze_rdf_east */

static void
maze_rdf_south(MAZE mz, int row, int col)
{
	if (row+1 >= mz->rows
			|| mz->cells[row+1][col]
				& VISITED_MARK)
		return;
	mz->cells[row++][col] &= ~SOUTH_WALL;
	mz->cells[row][col]   &= ~NORTH_WALL;
	maze_rdf(mz, row, col);
} /* maze_rdf_south */

static void
maze_rdf_west(MAZE mz, int row, int col)
{
	if (col-1 < 0
			|| mz->cells[row][col-1] & VISITED_MARK)
		return;
	mz->cells[row][col--] &= ~WEST_WALL;
	mz->cells[row][col]   &= ~EAST_WALL;
	maze_rdf(mz, row, col);
} /* maze_rdf_west */

static char n0[]  = {  1,  2,  4,  8 };
static char n1[]  = {  3,  5,  9 };
static char n2[]  = {  3,  6, 10 };
static char n3[]  = {  7, 11 };
static char n4[]  = {  5,  6, 12 };
static char n5[]  = {  7, 13 };
static char n6[]  = {  7, 14 };
static char n7[]  = { 15 };
static char n8[]  = {  9, 10, 12 };
static char n9[]  = { 11, 13 };
static char n10[] = { 11, 14 };
static char n11[] = { 15 };
static char n12[] = { 13, 14 };
static char n13[] = { 15 };
static char n14[] = { 15 };

static struct state_desc {
	int sz;
	char *nxt;
} tab_states[] = {

#define entry(_arg) { .sz = sizeof n##_arg, .nxt = n##_arg, }

	entry(0), entry(1), entry(2), entry(3),
	entry(4), entry(5), entry(6), entry(7),
	entry(8), entry(9), entry(10), entry(11),
	entry(12), entry(13), entry(14), 
}; /* tab_states */

static int n_tab_states = sizeof tab_states / sizeof tab_states[0];

void
maze_rdf(MAZE mz, int row, int col)
{
	mz->cells[row][col] |= VISITED_MARK;
	mz->to_visit--;
	int state = 0;
	while (state < n_tab_states) {
		struct state_desc *p = tab_states + state;	
		int next = p->nxt[random() % p->sz];
		int bit = state ^ next;
		if (bit & NORTH_WALL)	maze_rdf_north(mz, row, col);
		if (bit & EAST_WALL)	maze_rdf_east(mz, row, col);
		if (bit & SOUTH_WALL)	maze_rdf_south(mz, row, col);
		if (bit & WEST_WALL)	maze_rdf_west(mz, row, col);
		state = next;
	}
} /* maze_rdf */
