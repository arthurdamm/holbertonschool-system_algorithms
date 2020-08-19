#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queues.h"

/**
 * struct point_s - Structure storing coordinates
 *
 * @x: X coordinate
 * @y: Y coordinate
 */
typedef struct point_s
{
	int x;
	int y;
} point_t;


queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target);
int backtrack(char **map, int rows, int cols, point_t const *start,
	point_t const *target, int x, int y, queue_t *path);

#endif
