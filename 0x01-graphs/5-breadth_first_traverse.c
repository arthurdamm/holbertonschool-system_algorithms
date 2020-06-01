#include "graphs.h"

static size_t *visited;

/**
 * queue_push - pushes node onto queue
 * @queue: address of queue
 * @vertex: address of vertex
 * @depth: depth of vertex
 * Return: 1 on success else 0 on error
 */
int queue_push(queue_t *queue, vertex_t *vertex, size_t depth)
{
	node_t *node;

	node = calloc(1, sizeof(node_t));
	if (!node)
	{
		/* free queue */
		return (0);
	}
	node->vertex = vertex;
	node->depth = depth;
	if (!queue->tail)
	{
		queue->tail = queue->head = node;
	}
	else
	{
		queue->tail->next = node;
		queue->tail = node;
	}
	queue->size++;
	/* printf("Added [%s] [%lu]\n", vertex->content, queue->size); */
	return (1);
}

/**
 * queue_pop - pops node from front of queue
 * @queue: address of queue
 * @vertex: address of pointer to vertex
 * @depth: address of depth of vertex
 * Return: 1 on success else 0 on error
 */
int queue_pop(queue_t *queue, vertex_t **vertex, size_t *depth)
{
	node_t *node;

	if (!queue || !queue->head)
		return (0);
	node = queue->head;
	queue->head = queue->head->next;
	if (!queue->head)
		queue->tail = NULL;
	*vertex = node->vertex;
	queue->size--;
	*depth = node->depth;
	free(node);
	return (1);
}

/**
 * breadth_first_traverse - BFS
 * @graph: pointer to graph object
 * @action: pointer to traverse function
 * Return: max depth
 */
size_t breadth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth))
{
	queue_t *queue;
	vertex_t *vertex, *node_vertex;
	edge_t *edge;
	size_t max_depth = 0, node_depth, i, sz;

	if (!graph || !action || !graph->nb_vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(size_t));
	if (!visited)
		return (0);
	queue = calloc(1, sizeof(queue_t));
	if (!queue)
		return (free(visited), 0);
	for (vertex = graph->vertices; vertex; vertex = vertex->next)
	{
		if (!visited[vertex->index])
		{
			visited[vertex->index] = 1;
			queue_push(queue, vertex, 0);
		}
		while (queue->size)
		{
			for (i = 0, sz = queue->size; i < sz; i++)
			{
				queue_pop(queue, &node_vertex, &node_depth);
				action(node_vertex, node_depth);
				max_depth = max_depth > node_depth ? max_depth : node_depth;
				for (edge = node_vertex->edges; edge; edge = edge->next)
				{
					if (visited[edge->dest->index])
						continue;
					visited[edge->dest->index] = 1;
					queue_push(queue, edge->dest, node_depth + 1);
				}
			}
		}
	}
	free(visited);
	return (max_depth);
}
