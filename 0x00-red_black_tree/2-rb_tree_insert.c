#include "rb_trees.h"

/**
 * rb_tree_insert - inserts node into RB Tree
 * @tree: address of pointer to root node
 * @value: new value to insert
 * Return: new node on success else NULL
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *node, *prev = NULL, *curr;

	if (!tree)
		return (NULL);
	curr = *tree;
	while (curr)
	{
		prev = curr;
		if (value < curr->n)
			curr = curr->left;
		else if (value > curr->n)
			curr = curr->right;
		else
			return (NULL);
	}
	node = rb_tree_node(prev, value, RED);
	if (!node)
		return (NULL);
	if (!prev)
	{
		node->color = BLACK;
		return (*tree = node);
	}
	if (value < prev->n)
		prev->left = node;
	else
		prev->right = node;
	/* printf("BEFORE FIX:\n"); rb_tree_print(*tree); */
	rb_tree_insert_fix(tree, node);
	return (node);
}

/**
 * rb_tree_insert_fix - fixes RB Tree properties after insert
 * @tree: address of pointer to root node
 * @node: pointer to node inserted node to start fix
 * Return: pointer to inserted node
 */
rb_tree_t *rb_tree_insert_fix(rb_tree_t **tree, rb_tree_t *node)
{
	while (node->parent && node->parent->color == RED)
	{
		/* printf("WHILE:[%d] PARENT[%d]\n", node->n, node->parent->n); */
		if (node->parent->parent->left == node->parent)
		{
			node = fix_right_uncle(tree, node);
		}
		else
		{
			node = fix_left_uncle(tree, node);
		}
	}
	(*tree)->color = BLACK;
	return (node);
}

/**
 * fix_right_uncle - fixes RB subtree relative to right uncle
 * @tree: address of pointer to root node
 * @node: pointer to node inserted node to start fix
 * Return: pointer to inserted node
 */
rb_tree_t *fix_right_uncle(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *uncle = node->parent->parent->right;

	/* printf("FIX RIGHT UNCLE [%d]\n", node->n); */
	if (uncle && uncle->color == RED)
	{
		uncle->color = BLACK;
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		node = node->parent->parent;
	}
	else
	{
		if (node == node->parent->right)
		{
			node = node->parent;
			left_rotate(tree, node);
		}
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		right_rotate(tree, node->parent->parent);
	}
	return (node);
}

/**
 * fix_left_uncle - fixes RB subtree relative to left uncle
 * @tree: address of pointer to root node
 * @node: pointer to node inserted node to start fix
 * Return: pointer to inserted node
 */
rb_tree_t *fix_left_uncle(rb_tree_t **tree, rb_tree_t *node)
{
	rb_tree_t *uncle = node->parent->parent->left;

	/* printf("FIX LEFT UNCLE [%d]\n", node->n); */
	if (uncle && uncle->color == RED)
	{
		uncle->color = BLACK;
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		node = node->parent->parent;
	}
	else
	{
		if (node == node->parent->left)
		{
			node = node->parent;
			right_rotate(tree, node);
		}
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
		left_rotate(tree, node->parent->parent);
	}
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
