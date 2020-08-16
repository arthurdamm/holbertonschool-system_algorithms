#include "huffman.h"

/**
 * huffman_extract_and_insert - extracts two node and inserts as one
 * @priority_queue: our huffman priorty queue to act upon
 * Return: 1 on success else 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *nested;
	symbol_t *symbol;

	if (!priority_queue || priority_queue->size < 2)
		return (0);
	node1 = heap_extract(priority_queue);
	node2 = heap_extract(priority_queue);
	if (!node1 || !node2)
		return (0);
	symbol = symbol_create(-1,
		((symbol_t *)node1->data)->freq + ((symbol_t *)node2->data)->freq);
	if (!symbol)
		return (0);
	nested = binary_tree_node(NULL, symbol);
	if (!nested)
		return (free(symbol), 0);
	nested->left = node1;
	nested->right = node2;
	node1->parent = nested;
	node2->parent = nested;
	if (heap_insert(priority_queue, nested))
		return (1);
	return (0);
}
