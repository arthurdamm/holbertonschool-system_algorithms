#include "rb_trees.h"

/**
 * array_to_rb_tree - inserts all elements to form RB Tree
 * @array: array of elements to insert
 * @size: size of array
 * Return: pointer to root node of RB Tree or NULL
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	int *stop;
	rb_tree_t *tree = NULL;

	for (stop = array + size; array < stop; array++)
		rb_tree_insert(&tree, *array);
	return (tree);
}
