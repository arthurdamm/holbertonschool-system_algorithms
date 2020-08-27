#include "nary_trees.h"

static size_t diameter;

/**
 * nary_tree_diameter - finds the diameter of n-ary tree
 * @root: pointer to root of tree
 * Return: diameter - max distnance between any two leaves
 */
size_t nary_tree_diameter(nary_tree_t const *root)
{
	if (!root)
		return (0);
	max_heights(root);
	return (diameter + 1);
}

/**
 * max_heights - finds the max heights of n-ary tree
 * @root: pointer to current root of subtree
 * Return: max height of this root
 */
size_t max_heights(nary_tree_t const *root)
{
	size_t max1 = 0, max2 = 0, h;
	nary_tree_t *child;

	if (!root)
		return (0);

	for (child = root->children; child; child = child->next)
	{
		h = max_heights(child);
		if (h > max1)
			max2 = max1, max1 = h;
		else if (h > max2)
			max2 = h;
	}
	diameter = MAX(diameter, max1 + max2);
	return (MAX(max1, max2) + 1);
}
