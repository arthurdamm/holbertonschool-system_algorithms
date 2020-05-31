#include "graphs.h"

#define FAILED_SRC	1
#define FAILED_DEST	2
#define FAILED_BOTH	3

int get_vertices_and_edges(graph_t *graph, const char *src, const char *dest,
	vertex_t **_src_v, edge_t **_src_e, vertex_t **_dest_v, edge_t **_dest_e,
	edge_type_t type);

/**
 * graph_add_edge - adds edge to graph
 * @graph: pointer to graph object
 * @src: name of source vertex
 * @dest: name of destination vertex
 * @type: type of edge UNI/BI
 * Return: 1 on success else 0
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
	edge_type_t type)
{
	vertex_t *src_v = NULL, *dest_v = NULL;
	edge_t *src_e, *src_e_new, *dest_e, *dest_e_new;
	int failed;

	if (!graph || !src || !dest)
		return (0);
	failed = get_vertices_and_edges(graph, src, dest, &src_v, &src_e,
		&dest_v, &dest_e, type);
	if (failed == FAILED_BOTH)
		return (0);
	if (!(failed & FAILED_SRC))
	{
		src_e_new = calloc(1, sizeof(edge_t));
		if (!src_e_new)
			return (0);
	}
	if (type == BIDIRECTIONAL && !(failed & FAILED_DEST))
	{
		dest_e_new = calloc(1, sizeof(edge_t));
		if (!dest_e_new)
			return (free(src_e_new), 0);
		dest_v->nb_edges++;
		dest_e_new->dest = src_v;
		if (dest_e)
			dest_e->next = dest_e_new;
		else
			dest_v->edges = dest_e_new;

	}
	if (!(failed & FAILED_SRC))
	{
		src_v->nb_edges++;
		src_e_new->dest = dest_v;
		if (src_e)
			src_e->next = src_e_new;
		else
			src_v->edges = src_e_new;
	}
	return (1);
}

int get_vertices_and_edges(graph_t *graph, const char *src, const char *dest,
	vertex_t **_src_v, edge_t **_src_e, vertex_t **_dest_v, edge_t **_dest_e,
	edge_type_t type)
{
	vertex_t *src_v = NULL, *dest_v = NULL, *curr_v;
	edge_t *src_e = NULL, *dest_e = NULL;
	int failed = 0;

	for (curr_v = graph->vertices; curr_v; curr_v = curr_v->next)
	{
		if (!src_v && !strcmp(src, curr_v->content))
			src_v = curr_v;
		else if (!dest_v && !strcmp(dest, curr_v->content))
			dest_v = curr_v;
	}
	if (!src_v || !dest_v)
		return (FAILED_BOTH);
	for (src_e = src_v->edges; src_e; src_e = src_e->next)
	{
		if (src_e->dest == dest_v)
		{
			failed |= FAILED_SRC;
			break;
		}
		if (!src_e->next)
			break;
	}
	for (dest_e = dest_v->edges; dest_e; dest_e = dest_e->next)
	{
		if (dest_e->dest == src_v)
		{
			failed |= FAILED_DEST;
			break;
		}
		if (!dest_e->next)
			break;
	}
	if (type == UNIDIRECTIONAL && failed & FAILED_SRC)
		return (FAILED_BOTH);
	*_src_v = src_v;
	*_src_e = src_e;
	*_dest_v = dest_v;
	*_dest_e = dest_e;
	return (failed);
}
