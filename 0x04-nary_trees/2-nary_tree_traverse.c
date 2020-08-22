#include "nary_trees.h"

/**
 * nary_tree_traverse - traverses entire n-ary tree
 * @root: pointer to root of tree
 * @action: action to take at each node
 * Return: Largest depth traversed
 */
size_t nary_tree_traverse(nary_tree_t const *root,
	void (*action)(nary_tree_t const *node, size_t depth))
{
	if (!root || !action)
		return (0);
	return (_nary_tree_traverse(root, action, 0));
}

/**
 * _nary_tree_traverse - traverses entire n-ary tree
 * @root: pointer to root of tree
 * @action: action to take at each node
 * @depth: current traversal depth
 * Return: Largest depth traversed
 */
size_t _nary_tree_traverse(nary_tree_t const *root,
	void (*action)(nary_tree_t const *node, size_t depth), size_t depth)
{
	size_t max_depth = depth, temp_depth;

	if (!root)
		return (0);
	action(root, depth);
	temp_depth = _nary_tree_traverse(root->children, action, depth + 1);
	max_depth = MAX(max_depth, temp_depth);
	temp_depth = _nary_tree_traverse(root->next, action, depth);
	max_depth = MAX(max_depth, temp_depth);
	return (max_depth);
}
