#include "heap.h"

/**
 * heap_delete - frees the entire heap structure
 * @heap: pointer to heap struct
 * @free_data: pointer to data-freeing function
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	setbuf(stdout, NULL);
	if (!heap)
		return;
	recursively_free(heap->root, free_data);
	free(heap);
}

/**
 * recursively_free - frees the tree recursively
 * @root: pointer to root of current subtree
 * @free_data: pointer to data-freeing function
 */
void recursively_free(binary_tree_node_t *root, void (*free_data)(void *))
{
	if (!root)
		return;
	recursively_free(root->left, free_data);
	recursively_free(root->right, free_data);
	if (free_data)
		free_data(root->data);
	free(root);
}
