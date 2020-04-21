#include "rb_trees.h"

rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *node = root;

	while (node)
	{
		if (n > node->n)
			node = node->right;
		else if (n < node->n)
			node = node->left;
		else
			break;
	}
	if (!node)
		return (root);
	rb_tree_remove_node(&root, node);
	return (root);
}

void rb_tree_remove_node(rb_tree_t **tree, rb_tree_t *z)
{
	rb_tree_t *x, *y = z;
	int y_color = y->color;

	printf("RM NODE [%d]\n", z->n);
	if (!z->left)
	{
		printf("RM CASE 1\n");
		x = z->right;
		rb_tree_replace(tree, z, z->right);
	}
	else if (!z->right)
	{
		printf("RM CASE 2\n");
		x = z->left;
		rb_tree_replace(tree, z, z->left);
	}
	else
	{
		printf("RM CASE 3\n");
		y = z->right;
		while (y && y->left)
			y = y->left;
		y_color = y->color;
		x = y->right;
		if (y->parent != z)
		{
			rb_tree_replace(tree, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rb_tree_replace(tree, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (y_color == BLACK)
		rb_tree_remove_fixup(tree, x);
	free(z);
}

void rb_tree_remove_fixup(rb_tree_t **tree, rb_tree_t *x)
{
	if (!x)
	{
		printf("X IS NULL!\n");
		return;
	}
	
	while (x != *tree && x->color == BLACK)
		if (x == x->parent->left)
			x = rb_tree_fix_right_sibling(tree, x);
		else
			x = rb_tree_fix_left_sibling(tree, x);
	x->color = BLACK;
}

rb_tree_t *rb_tree_fix_right_sibling(rb_tree_t **tree, rb_tree_t *x)
{
	rb_tree_t *w = x->parent->right;

	if (w->color == RED)
	{
		w->color = BLACK;
		x->parent->color = RED;
		left_rotate(tree, x->parent);
		w = x->parent->right;
	}
	if (w->left->color == BLACK && w->right->color == BLACK)
	{
		w->color = RED;
		x = x->parent;
	}
	else
	{
		if (w->right->color == BLACK)
		{
			w->left->color = BLACK;
			w->color = RED;
			left_rotate(tree, w);
			w = x->parent->right;
		}
		w->color = x->parent->color;
		x->parent->color = BLACK;
		w->right->color = BLACK;
		left_rotate(tree, x->parent);
		x = *tree;
	}
	return (x);
}

rb_tree_t *rb_tree_fix_left_sibling(rb_tree_t **tree, rb_tree_t *x)
{
	rb_tree_t *w = x->parent->left;

	if (w->color == RED)
	{
		w->color = BLACK;
		x->parent->color = RED;
		right_rotate(tree, x->parent);
		w = x->parent->left;
	}
	if (w->left->color == BLACK && w->right->color == BLACK)
	{
		w->color = RED;
		x = x->parent;
	}
	else
	{
		if (w->left->color == BLACK)
		{
			w->right->color = BLACK;
			w->color = RED;
			right_rotate(tree, w);
			w = x->parent->left;
		}
		w->color = x->parent->color;
		x->parent->color = BLACK;
		w->left->color = BLACK;
		right_rotate(tree, x->parent);
		x = *tree;
	}
	return (x);
}

void rb_tree_replace(rb_tree_t **tree, rb_tree_t *before, rb_tree_t *after)
{
	if (!before->parent)
		*tree = after;
	else if (before == before->parent->left)
		before->parent->left = after;
	else
		before->parent->right = after;
	if (after)
		after->parent = before->parent;
}
