#include "nary_trees.h"

/**
 * nary_tree_delete - deletes a n-ary tree
 * @tree: pointer to root node
 */
void nary_tree_delete(nary_tree_t *tree)
{
	if (!tree)
		return;
	nary_tree_delete(tree->next);
	nary_tree_delete(tree->children);
	free(tree->content);
	free(tree);
}
