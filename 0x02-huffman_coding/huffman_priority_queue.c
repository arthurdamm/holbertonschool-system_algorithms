#include "huffman.h"

/**
 * data_cmp - compares freq data in symbol struct
 * @node_a: the first node containing a symbol struct
 * @node_b: the second node containing a symbol struct
 * Return: the difference of the frequencies
 */
int data_cmp(void *node_a, void *node_b)
{
	symbol_t *symbol_a = ((binary_tree_node_t *)node_a)->data,
		*symbol_b = ((binary_tree_node_t *)node_b)->data;
	return (symbol_a->freq - symbol_b->freq);
}

/**
 * free_data - frees the nested node
 * @data: pointer to nested node
 */
void free_data(void *data)
{
	free(((binary_tree_node_t *)data)->data);
	free(data);
}

/**
 * huffman_priority_queue - creates priority queue from freq data
 * @data: array of characters
 * @freq: associated frequency of characters
 * @size: size of passed arrays
 * Return: pointer to priority queue
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	size_t i;
	heap_t *heap;
	binary_tree_node_t *node, *nested;
	symbol_t *symbol;

	if (!size || !data || !freq)
		return (NULL);
	heap = heap_create(data_cmp);
	if (!heap)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		nested = binary_tree_node(NULL, symbol);
		if (!symbol || !nested)
		{
			free(symbol);
			free(nested);
			heap_delete(heap, free_data);
			return (NULL);
		}
		node = heap_insert(heap, nested);
		if (!node)
		{
			heap_delete(heap, free_data);
			return (NULL);
		}
	}
	return (heap);
}
