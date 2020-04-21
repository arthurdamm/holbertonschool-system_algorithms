#include <stdlib.h>
#include "rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);

/**
 * main - Entry point
 *
 * Return: 0 on success, error code on failure
 */
int main(void)
{
	rb_tree_t *tree;
	int array[] = {
		79, 47, 68, 87, 84, 91, 21, 32, 34, 2,
		20, 22
	};
	ssize_t n = sizeof(array) / sizeof(array[0]);

	tree = array_to_rb_tree(array, n);
	if (!tree)
		return (1);
	rb_tree_print(tree);
	for (n--; n >= 0; n--)
	{
		tree = rb_tree_remove(tree, array[n]);
		rb_tree_print(tree);
		printf("REMOVED [%d]\n", array[n]);
		if (!rb_tree_is_valid(tree))
		{
			printf("Error tree invalid!\n");
			return (0);
		}
	}
	return (0);
}
