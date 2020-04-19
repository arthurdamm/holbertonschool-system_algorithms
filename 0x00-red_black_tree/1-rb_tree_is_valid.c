#include "rb_trees.h"

/**
 * _rb_tree_is_valid - recursively valildates RB tree properties
 * @tree: pointer to root of tree to validate
 * Return: 1 if valid else 0
 */
int _rb_tree_is_valid(const rb_tree_t *tree, size_t *min_height, size_t *max_height)
{
	size_t min_height_right = 0, max_height_right = 0;
	short valid = 0;

	if (!tree)
	{
		*min_height = *max_height = 0;
		return (1);
	}
	if (tree->color != RED && tree->color != BLACK)
		return (0);
	if (tree->color == RED)
	{
		if (tree->left && tree->left->color != BLACK)
			return (0);
		if (tree->right && tree->right->color != BLACK)
			return (0);
	}
	valid |= _rb_tree_is_valid(tree->left, min_height, max_height);
	valid |= _rb_tree_is_valid(tree->right, &min_height_right, &max_height_right);
	if (!valid)
		return (0);
	*min_height = 1 + MIN(*min_height, min_height_right);
	*max_height = 1 + MAX(*max_height, max_height_right);
	return (*max_height <= *min_height * 2);
}

/**
 * rb_tree_is_valid - valildates RB tree properties
 * @tree: pointer to root of tree to validate
 * Return: 1 if valid else 0
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	size_t min_height = 0, max_height = 0;

	if (!tree)
		return (0);
	return (_rb_tree_is_valid(tree, &min_height, &max_height));
}
