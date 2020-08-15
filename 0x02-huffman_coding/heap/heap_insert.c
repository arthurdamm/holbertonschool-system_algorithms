#include "heap.h"

/**
 * convert - converts a number to a custom base
 * @num: the number to convert
 * @base: the desired base
 * Return: pointer to string containing digits in new base
 */
char *convert(long num, long base)
{
	char *DIGITS = "0123456789ABCDEFG", *ptr;
	static char buf[66];
	short neg = num < 0 ? 1 : 0;

	ptr = &buf[sizeof(buf)];
	*--ptr = 0;
	do {
		*--ptr = DIGITS[ABS(num % base)];
		num /= base;
	} while (num);
	if (neg)
		*--ptr = '-';
	return (ptr);
}

/**
 * heap_insert - inserts new node into min heap
 * @heap: pointer to heap structure
 * @data: pointer to data
 * Return: pointer to new node or NULL
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	size_t i;
	binary_tree_node_t *new_node, *node;
	char *bitstr;
	void *temp;

	if (!heap)
		return (NULL);
	new_node = binary_tree_node(NULL, data);
	if (!new_node)
		return (NULL);
	heap->size++;
	if (!heap->root)
		return (heap->root = new_node);
	bitstr = convert(heap->size, 2);
	for (node = heap->root, i = 1; i < strlen(bitstr) - 1; i++)
		node = bitstr[i] == '1' ? node->right : node->left;
	if (bitstr[i] == '1')
		node->right = new_node;
	else
		node->left = new_node;
	new_node->parent = node;
	node = new_node;
	while (node->parent && heap->data_cmp(node->parent->data, node->data) > 0)
	{
		temp = node->data;
		node->data = node->parent->data;
		node->parent->data = temp;
		node = node->parent;
	}
	return (new_node);
}
