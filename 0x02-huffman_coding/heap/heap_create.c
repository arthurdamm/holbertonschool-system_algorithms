#include "heap.h"

/**
 * heap_create - allocates new heap structure
 * @data_cmp: the comparison function
 * Return: pointer to heap_s or NULL
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap = NULL;

	heap = malloc(sizeof(*heap));
	if (!heap)
		return (NULL);
	heap->root = NULL;
	heap->size = 0;
	heap->data_cmp = data_cmp;
	return (heap);
}
