#include "graphs.h"

/**
 * graph_create - creates a graph
 * Return: node to graph
 */
graph_t *graph_create(void)
{
	return (calloc(1, sizeof(graph_t)));
}
