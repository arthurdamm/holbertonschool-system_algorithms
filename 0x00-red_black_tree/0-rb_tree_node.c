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

/**
 * left_rotate - rotates subtree left
 * @tree: address of pointer to root node
 * @node: pointer to node inserted node to start fix
 */
void left_rotate(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *child = node->right;

	if (!child)
		return;
	/* printf("LEFT ROTATE:[%d]\n", node->n); */
	node->right = child->left;
	if (child->left)
		child->left->parent = node;
	child->left = node;
	child->parent = node->parent;
	if (!node->parent)
		*tree = child;
	else if (node->parent->left == node)
		node->parent->left = child;
	else
		node->parent->right = child;
	node->parent = child;
}

/**
 * right_rotate - rotates subtree right
 * @tree: address of pointer to root node
 * @node: pointer to node inserted node to start fix
 */
void right_rotate(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *child = node->left;

	if (!child)
		return;
	/* printf("RIGHT ROTATE:[%d]\n", node->n); */
	node->left = child->right;
	if (child->right)
		child->right->parent = node;
	child->right = node;
	child->parent = node->parent;
	if (!node->parent)
		*tree = child;
	else if (node->parent->left == node)
		node->parent->left = child;
	else
		node->parent->right = child;
	node->parent = child;
}
