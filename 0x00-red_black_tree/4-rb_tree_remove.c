#include "rb_trees.h"

rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *node = root;

	printf("TRY RM [%d]\n", n);
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
	rb_tree_t *x, *x_parent = NULL, *y = z;
	int y_color = y->color;

	printf("RM NODE [%d]\n", z->n);
	if (!z->left)
	{
		printf("RM CASE 1\n");
		x = z->right;
		x_parent = z->parent;
		rb_tree_replace(tree, z, z->right);
	}
	else if (!z->right)
	{
		printf("RM CASE 2\n");
		x = z->left;
		x_parent = z->parent;
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
		if (y->parent == z)
		{
			if (x)
				x->parent = y;
			x_parent = y;
		}
		else
		{
			rb_tree_replace(tree, y, y->right);
			x_parent = y->parent;
			y->right = z->right;
			y->right->parent = y;
		}
		rb_tree_replace(tree, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	rb_tree_print(*tree);
	printf("y is [%d] x is [%d] x_parent is [%d]\n", y->n, x ? x->n : 0, x_parent ? x_parent->n : 0);
	if (y_color == BLACK)
		rb_tree_remove_fixup(tree, x, x_parent);
	free(z);
}

void rb_tree_remove_fixup(rb_tree_t **tree, rb_tree_t *x, rb_tree_t *x_parent)
{	
	while ((x && x != *tree && x->color == BLACK) || (!x && x_parent))
		if ((x && x == x->parent->left) || (!x && x_parent && x_parent->right))
		{
			x = rb_tree_fix_right_sibling(tree, x, x_parent);
			x_parent = NULL;
		}
		else if ((x && x == x->parent->right) || (x_parent && x_parent->left))
		{
			x = rb_tree_fix_left_sibling(tree, x, x_parent);
			x_parent = NULL;
		}
	if (x)
		x->color = BLACK;
}

rb_tree_t *rb_tree_fix_right_sibling(rb_tree_t **tree, rb_tree_t *x, rb_tree_t *x_parent)
{
	rb_tree_t *w;

	if (!x_parent)
		x_parent = x->parent;
	w = x_parent->right;

	printf("FIX RIGHT SIBLING:\n");
	printf("X_PARENT is [%d] X\n", x_parent->n);
	printf("X is [%d]\n", x ? x->n : 0);
	printf("X parent is [%d]\n", x ? x->parent->n : 0);
	printf("X_PARENT->right is [%d] X\n", x_parent && x_parent->right ? x_parent->right->n : 0);
	if (w->color == RED)
	{
		w->color = BLACK;
		x_parent->color = RED;
		left_rotate(tree, x_parent);
		w = x_parent->right;
	}
	if (!w)
		return (x);
	if ((!w->left || w->left->color == BLACK) &&
		(!w->right || w->right->color == BLACK))
	{
		w->color = RED;
		x = x_parent;
	}
	else
	{
		if (!w->right || w->right->color == BLACK)
		{
			printf("CASE 3\n");
			w->left->color = BLACK;
			w->color = RED;
			right_rotate(tree, w);
			w = x_parent->right;
		}
		printf("CASE 4\n");
		w->color = x_parent->color;
		x_parent->color = BLACK;
		if (w->right)
			w->right->color = BLACK;
		left_rotate(tree, x_parent);
		x = *tree;
	}
	return (x);
}

rb_tree_t *rb_tree_fix_left_sibling(rb_tree_t **tree, rb_tree_t *x, rb_tree_t *x_parent)
{
	rb_tree_t *w;

	if (!x_parent)
		x_parent = x->parent;
	w = x_parent->left;

	printf("FIX LEFT SIBLING:\n");
	printf("X_PARENT is [%d] X\n", x_parent->n);
	printf("X is [%d]\n", x ? x->n : 0);
	printf("X parent is [%d]\n", x ? x->parent->n : 0);
	printf("X_PARENT->left is [%d] X\n", x_parent && x_parent->left ? x_parent->left->n : 0);
	if (w->color == RED)
	{
		w->color = BLACK;
		x_parent->color = RED;
		right_rotate(tree, x_parent);
		w = x_parent->left;
	}
	if ((!w->left || w->left->color == BLACK) &&
		(!w->right || w->right->color == BLACK))
	{
		w->color = RED;
		x = x_parent;
	}
	else
	{
		if (!w->left || w->left->color == BLACK)
		{
			printf("CASE 3\n");
			w->right->color = BLACK;
			w->color = RED;
			left_rotate(tree, w);
			w = x_parent->left;
		}
		printf("CASE 4\n");
		if (w)
			w->color = x_parent->color;
		x_parent->color = BLACK;
		if (w && w->left)
			w->left->color = BLACK;
		right_rotate(tree, x_parent);
		x = *tree;
		/* if (!w->left || w->left->color == BLACK)
		{
			printf("CASE 3\n");
			w->right->color = BLACK;
			w->color = RED;
			right_rotate(tree, w);
			w = x_parent->left;
		}
		printf("CASE 4\n");
		w->color = x_parent->color;
		x_parent->color = BLACK;
		if (w->left)
			w->left->color = BLACK;
		right_rotate(tree, x_parent); */
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
