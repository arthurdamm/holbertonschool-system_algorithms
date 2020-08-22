#include "nary_trees.h"

/**
 * nary_tree_insert - inserts node into n-ary tree
 * @parent: pointer to parent node or NULL
 * @_str: value of node
 * Return: pointer to new node or NULL
 */
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *_str)
{
	nary_tree_t *new = calloc(1, sizeof(*new));
	char *str = strdup(_str);

	if (!new || !str)
		return (free(new), free(str), NULL);

	new->content = str;
	if (!parent)
		return (new);
	new->next = parent->children;
	parent->children = new;
	parent->nb_children++;
	return (new);
}
