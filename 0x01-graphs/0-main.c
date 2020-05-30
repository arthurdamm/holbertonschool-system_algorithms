#include <stdlib.h>
#include <stdio.h>

#include "graphs.h"

/**
 * main - Entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	graph_t *graph;

	graph = graph_create();
	if (!graph)
	{
		fprintf(stderr, "Failed to create graph\n");
		return (EXIT_FAILURE);
	}

	printf("Successfully created graph\n");
	printf("size:[%lu] v:[%p]\n", graph->nb_vertices, (void *)graph->vertices);
	graph_display(graph);

	return (EXIT_SUCCESS);
}
