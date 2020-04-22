#ifndef RB_TREES_H
#define RB_TREES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

/**
 * enum rb_color_e - Possible color of a Red-Black tree
 *
 * @RED: 0 -> Red node
 * @BLACK: 1 -> Black node
 * @DOUBLE_BLACK: 2 -> Unknown
 */
typedef enum rb_color_e
{
	RED = 0,
	BLACK,
	DOUBLE_BLACK
} rb_color_t;

/**
 * struct rb_tree_s - Red-Black tree node structure
 *
 * @n: Integer stored in the node
 * @parent: Pointer to the parent node
 * @left: Pointer to the left child node
 * @right: Pointer to the right child node
 * @color: Color of the node (RED or BLACK)
 */
typedef struct rb_tree_s
{
	int n;
	rb_color_t color;
	struct rb_tree_s *parent;
	struct rb_tree_s *left;
	struct rb_tree_s *right;
} rb_tree_t;

void rb_tree_print(const rb_tree_t *tree);

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color);
int rb_tree_is_valid(const rb_tree_t *tree);

rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value);
rb_tree_t *rb_tree_insert_fix(rb_tree_t **tree, rb_tree_t *node);
rb_tree_t *fix_right_uncle(rb_tree_t **tree, rb_tree_t *node);
rb_tree_t *fix_left_uncle(rb_tree_t **tree, rb_tree_t *node);
void left_rotate(rb_tree_t **tree, rb_tree_t *node);
void right_rotate(rb_tree_t **tree, rb_tree_t *node);

rb_tree_t *array_to_rb_tree(int *array, size_t size);

rb_tree_t *rb_tree_remove(rb_tree_t *root, int n);
void rb_tree_remove_node(rb_tree_t **tree, rb_tree_t *z);
void rb_tree_remove_fixup(rb_tree_t **tree, rb_tree_t *x, rb_tree_t *x_parent);
rb_tree_t *rb_tree_fix_right_sibling(rb_tree_t **tree, rb_tree_t *x,
	rb_tree_t *x_parent);
rb_tree_t *rb_tree_fix_left_sibling(rb_tree_t **tree, rb_tree_t *x,
	rb_tree_t *x_parent);
void rb_tree_replace(rb_tree_t **tree, rb_tree_t *before, rb_tree_t *after);

#endif
