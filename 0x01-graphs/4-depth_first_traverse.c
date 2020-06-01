#include "graphs.h"

static size_t *visited;

/**
 * max - returns max of 2 values
 * @a: value a
 * @b: value b
 * Return: max of a, b
 */
size_t max(size_t a, size_t b)
{
	return (a > b ? a : b);
}

/**
 * dfs - depth first search
 * @vertex: pointer to vertex object
 * @action: pointer to traverse function
 * @depth: current recursion depth
 * Return: max depth
 */
size_t dfs(vertex_t *vertex, void (*action)(const vertex_t *v, size_t depth),
	size_t depth)
{
	edge_t *edge;
	size_t max_depth = depth;

	if (!vertex || visited[vertex->index])
		return (depth > 1 ? depth - 1 : 0);
	visited[vertex->index] = 1;
	action(vertex, depth);
	for (edge = vertex->edges; edge; edge = edge->next)
		max_depth = max(dfs(edge->dest, action, depth + 1), max_depth);
	return (max_depth);
}

/**
 * depth_first_traverse - DFS
 * @graph: pointer to graph object
 * @action: pointer to traverse function
 * Return: max depth
 */
size_t depth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	size_t max_depth = 0;

	if (!graph || !action)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(size_t));
	if (!visited)
		return (0);
	max_depth = max(dfs(graph->vertices, action, 0), max_depth);
	free(visited);
	return (max_depth);
}
