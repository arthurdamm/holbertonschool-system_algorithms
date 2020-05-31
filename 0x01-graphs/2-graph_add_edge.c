#include "graphs.h"

int get_vertices_and_edges(graph_t *graph, const char *src, const char *dest,
	vertex_t **_src_v, edge_t **_src_e, vertex_t **_dest_v, edge_t **_dest_e);

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

	if (!graph || !src || !dest)
		return (0);
	if (!get_vertices_and_edges(graph, src, dest, &src_v, &src_e,
		&dest_v, &dest_e))
		return (0);
	src_e_new = calloc(1, sizeof(edge_t));
	if (!src_e_new)
		return (0);
	if (type == BIDIRECTIONAL)
	{
		dest_e_new = calloc(1, sizeof(edge_t));
		if (!dest_e_new)
		{
			free(src_e_new);
			return (0);
		}
		dest_v->nb_edges++;
		dest_e_new->dest = src_v;
		if (dest_e)
			dest_e->next = dest_e_new;
		else
			dest_v->edges = dest_e_new;

	}
	src_v->nb_edges++;
	src_e_new->dest = dest_v;
	if (src_e)
		src_e->next = src_e_new;
	else
		src_v->edges = src_e_new;
	return (1);
}

int get_vertices_and_edges(graph_t *graph, const char *src, const char *dest,
	vertex_t **_src_v, edge_t **_src_e, vertex_t **_dest_v, edge_t **_dest_e)
{
	vertex_t *src_v = NULL, *dest_v = NULL, *curr_v;
	edge_t *src_e = NULL, *dest_e = NULL;

	for (curr_v = graph->vertices; curr_v; curr_v = curr_v->next)
	{
		if (!src_v && !strcmp(src, curr_v->content))
			src_v = curr_v;
		else if (!dest_v && !strcmp(dest, curr_v->content))
			dest_v = curr_v;
	}
	if (!src_v || !dest_v)
		return (0);
	for (src_e = src_v->edges; src_e; src_e = src_e->next)
	{
		if (src_e->dest == dest_v)
			return (0);
		if (!src_e->next)
			break;
	}
	for (dest_e = dest_v->edges; dest_e; dest_e = dest_e->next)
	{
		if (dest_e->dest == src_v)
			return (0);
		if (!dest_e->next)
			break;
	}
	*_src_v = src_v;
	*_src_e = src_e;
	*_dest_v = dest_v;
	*_dest_e = dest_e;
	return (1);
}
