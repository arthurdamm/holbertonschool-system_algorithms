#include "nary_trees.h"

/**
 * path_exists - checks if a certain path exists thru tree
 * @root: pointer to root of the tree
 * @path: NULL terminated array of node content to traverse
 * Return: 1 if path exits else 0
 */
int path_exists(nary_tree_t const *root, char const * const *path)
{
	if (!root || !path)
		return (0);
	return (_path_exists(root, path));
}

/**
 * _path_exists - recursively checks if a certain path exists thru tree
 * @root: pointer to root of the tree
 * @path: NULL terminated array of node content to traverse
 * Return: 1 if path exits else 0
 */
int _path_exists(nary_tree_t const *root, char const * const *path)
{
	nary_tree_t const *node;

	if (!*path)
		return (1);
	if (!root)
		return (0);
	for (node = root; node; node = node->next)
		if (!strcmp(node->content, *path))
			if (_path_exists(node->children, path + 1))
				return (1);
	return (0);
}
