#include "pathfinding.h"

/**
 * backtracking_array - uses backtracking to find path
 * @map: 2-D read-only character map 1 blocked, 0 walkable
 * @rows: number of rows in map
 * @cols: number of cols in map
 * @start: starting point (x, y)
 * @target: ending point (x, y)
 * Return: queue containing path of points
 */
queue_t *backtracking_array(char **map, int rows, int cols,
	point_t const *start, point_t const *target)
{
	queue_t *path = queue_create(), *reverse_path = queue_create();
	char **mymap;
	int i;
	point_t *point;

	if (!path || !reverse_path)
		return (NULL);
	mymap = malloc(rows * sizeof(char *));
	if (!mymap)
		exit(1);
	for (i = 0; i < rows; i++)
	{
		mymap[i] = malloc(cols);
		if (!mymap[i])
			exit(1);
		strcpy(mymap[i], map[i]);
		/* printf("%s\n", mymap[i]); */
	}

	if (backtrack(mymap, rows, cols, NULL, target, start->x, start->y, path))
	{
		while ((point = dequeue(path)))
			queue_push_front(reverse_path, point);
	}
	for (i = 0; i < rows; i++)
		; /* printf("%s\n", mymap[i]); */
	return (reverse_path);
}

int backtrack(char **map, int rows, int cols, point_t const *start,
	point_t const *target, int x, int y, queue_t *path)
{
	point_t *point;

	if (x < 0 || x >= cols || y < 0 || y >= rows || map[y][x] != '0')
		return (0);
	map[y][x] = '1';
	point = calloc(1, sizeof(*point));
	if (!point)
		exit(1);
	point->x = x;
	point->y = y;
	queue_push_front(path, point);
	printf("Checking coordinates [%d, %d]\n", x, y);
	if (x == target->x && y == target->y)
		return (1);
	if (backtrack(map, rows, cols, start, target, x + 1, y, path) ||
		backtrack(map, rows, cols, start, target, x, y + 1, path) ||
		backtrack(map, rows, cols, start, target, x - 1, y, path) ||
		backtrack(map, rows, cols, start, target, x, y - 1, path))
		return (1);
	free(dequeue(path));
	return (0);
}
