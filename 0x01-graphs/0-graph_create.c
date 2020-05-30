#include "graphs.h"

/**
 * graph_create - creates a graph
 * Return: node to graph
 */
graph_t *graph_create(void)
{
	graph_t *graph = NULL;

	graph = malloc(sizeof(graph_t));
	if (!graph)
		return (NULL);
	graph->nb_vertices = 0;
	graph->vertices = NULL;
	return (graph);
}
