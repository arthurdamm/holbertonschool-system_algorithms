#include "pathfinding.h"

static char *g_visited;
static queue_t *g_path;
static vertex_t const *g_target;
static graph_t *g_graph;

/**
 * backtracking_graph - uses backtracking to find path through graph
 * @graph: pointer to graph struct
 * @start: pointer to starting vertex
 * @target: pointer to target vertex
 * Return: queue of vertices forming path
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
	vertex_t const *target)
{
	queue_t *reverse_path = NULL;

	if (!graph || !start || !target)
		return (NULL);

	setbuf(stdout, NULL);
	g_visited = calloc(graph->nb_vertices, sizeof(*g_visited));
	g_path = queue_create();
	if (!g_visited || !g_path)
		exit(1);
	g_target = target;
	g_graph = graph;
	if (dfs(start))
	{
		char *city;

		reverse_path = queue_create();
		if (!reverse_path)
			exit(1);
		for (city = dequeue(g_path); city; city = dequeue(g_path))
			if (!queue_push_front(reverse_path, city))
				exit(1);
	}
	queue_delete(g_path);
	free(g_visited);
	return (reverse_path);
}

/**
 * dfs - uses DFS backtracking to find path
 * @vertex: current vertex to traverse
 * Return: 1 if destination found else 0
 */
int dfs(vertex_t const *vertex)
{
	char *city;
	edge_t *edge;

	if (g_visited[vertex->index])
		return (0);
	printf("Checking %s\n", vertex->content);
	g_visited[vertex->index] = 1;
	city = strdup(vertex->content);
	if (!city)
		exit(1);
	queue_push_front(g_path, city);
	if (vertex == g_target)
		return (1);
	for (edge = vertex->edges; edge; edge = edge->next)
		if (dfs(edge->dest))
			return (1);
	free(dequeue(g_path));
	return (0);
}
