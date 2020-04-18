#include "rb_trees.h"

/**
 * rb_tree_node - returns a new node to an RB tree
 * @parent: pointer to parent node
 * @value: integer value of new node
 * @color: the new node's RB color
 * Return: pointer to new node
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *node = malloc(sizeof(*node));

	if (!node)
		return (NULL);
	memset(node, 0, sizeof(*node));
	node->parent = parent;
	node->n = value;
	node->color = color;
	return (node);
}
