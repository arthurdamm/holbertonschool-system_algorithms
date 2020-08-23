#ifndef NARY_TREES_H
#define NARY_TREES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/**
 * struct nary_tree_s - N-ary tree node structure
 *
 * @content: Content of the node
 * @parent: Pointer to the parent node
 * @nb_children: Number of children
 * @children: Pointer to the head node of the children linked list
 * @next: Pointer to the next child in the parent's children linked list
 */
typedef struct nary_tree_s
{
	char				*content;
	struct nary_tree_s	*parent;
	size_t				nb_children;
	struct nary_tree_s	*children;
	struct nary_tree_s	*next;
} nary_tree_t;

nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *_str);
void nary_tree_delete(nary_tree_t *tree);

size_t nary_tree_traverse(nary_tree_t const *root,
	void (*action)(nary_tree_t const *node, size_t depth));
size_t _nary_tree_traverse(nary_tree_t const *root,
	void (*action)(nary_tree_t const *node, size_t depth), size_t depth);

size_t nary_tree_diameter(nary_tree_t const *root);
size_t max_heights(nary_tree_t const *root);

int path_exists(nary_tree_t const *root, char const * const *path);
int _path_exists(nary_tree_t const *root, char const * const *path);

#endif
