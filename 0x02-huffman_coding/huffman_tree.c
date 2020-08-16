#include "huffman.h"

/**
 * huffman_tree - creates a huffman tree from data
 * @data: character array
 * @freq: frequency of char array
 * @size: size of array args
 * Return: root node of huffman tree
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *heap = huffman_priority_queue(data, freq, size);
	binary_tree_node_t *root;

	setbuf(stdout, NULL);
	if (!heap)
		return (NULL);
	while (heap->size > 1)
	{
		if (!huffman_extract_and_insert(heap))
			return (NULL);
	}
	root = heap->root->data;
	free(heap->root);
	free(heap);
	return (root);
}
