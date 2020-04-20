#include <stdlib.h>
#include <stdio.h>
#include "rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);
void test1();
void test2();
void test3();

/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	test3();
	return (0);
}

void test1()
{
	rb_tree_t *root;
	rb_tree_t *node;

	root = NULL;
	node = rb_tree_insert(&root, 98);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 402);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 512);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 12);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 46);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 128);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 256);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 1);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 128);
	printf("Node should be nil -> %p\n", (void *)node);
	node = rb_tree_insert(&root, 624);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 780);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
}

void test2()
{
	rb_tree_t *root;
	rb_tree_t *node;

	root = NULL;
	node = rb_tree_insert(&root, 98);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 97);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 96);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 95);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 94);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 93);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 92);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 100);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 101);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 102);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 103);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
}

void test3()
{
	rb_tree_t *root;
	rb_tree_t *node;
	size_t i;

	root = NULL;

	for (i = 0; i < 8; i++)
	{
		node = rb_tree_insert(&root, i);
		printf("Inserted: %d\n", node->n);
		rb_tree_print(root);
	}
	rb_tree_print(root);
}
