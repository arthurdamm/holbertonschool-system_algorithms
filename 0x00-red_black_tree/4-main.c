#include <stdlib.h>
#include "rb_trees.h"
#include <limits.h>
#include <time.h>

void rb_tree_print(const rb_tree_t *tree);
rb_tree_t *valid_rb_1(void);
rb_tree_t *test_case_2(int **_arr, int *_n);
rb_tree_t *test_case_3(int **_arr, int *_n);
rb_tree_t *test_case_4(int **_arr, int *_n);
rb_tree_t *test_case_4b(int **_arr, int *_n);
int binary_tree_is_bst(const rb_tree_t *tree);
int *rand_array(int len, int max);
rb_tree_t *test_random_array(int len, int max, int *_n, int **array);

/**
 * main - Entry point
 *
 * Return: 0 on success, error code on failure
 */
int main(void)
{
	rb_tree_t *tree;
	/* int array[] = {
		79, 47, 68, 87, 84, 91, 21, 32, 34, 2,
		20, 22
	}; */
	int array[] = {
		10, 6, 5, 11
	};
	int *arr = array;
	int n = sizeof(array) / sizeof(array[0]);

	/* tree = array_to_rb_tree(array, n); */
	/* tree = valid_rb_1(); */
	tree = test_random_array(40, 50, &n, &arr);
	/* tree = test_case_2(&arr, &n); */
	/* tree = test_case_3(&arr, &n); */
	/* tree = test_case_4(&arr, &n); */
	/* tree = test_case_4b(&arr, &n); */
	if (!tree)
		return (1);
	rb_tree_print(tree);
	if (!rb_tree_is_valid(tree))
	{
		printf("Error tree invalid RB!\n");
		return (0);
	}
	else if (!binary_tree_is_bst(tree))
	{
		printf("Error tree invalid BST!\n");
		return (0);
	}
	else
	{
		printf("\nVALID TREE\n\n");
	}
	fflush(stdout);
	for (n--; n >= 0; n--)
	{
		tree = rb_tree_remove(tree, arr[n]);
		rb_tree_print(tree);
		printf("REMOVED [%d]\n", arr[n]);
		if (!rb_tree_is_valid(tree))
		{
			printf("Error tree invalid RB!\n");
			return (0);
		}
		else if (!binary_tree_is_bst(tree))
		{
			printf("Error tree invalid BST!\n");
			return (0);
		}
	}
	return (0);
}

/**
 * valid_rb_1 - Builds a valid R-B tree
 *
 * Return: A pointer to the created tree
 */
rb_tree_t *valid_rb_1(void)
{
	rb_tree_t *root;

	root = rb_tree_node(NULL, 10, BLACK);
	root->left = rb_tree_node(root, 5, BLACK);
	root->right = rb_tree_node(root, 11, BLACK);
	root->left->left = rb_tree_node(root->left, 4, RED);
	root->left->right = rb_tree_node(root->left, 6, RED);
	return (root);
}

rb_tree_t *test_case_1(void)
{
	rb_tree_t *root;

	root = rb_tree_node(NULL, 10, BLACK);
	root->left = rb_tree_node(root, 5, BLACK);
	root->right = rb_tree_node(root, 11, BLACK);
	root->left->left = rb_tree_node(root->left, 4, RED);
	root->left->right = rb_tree_node(root->left, 6, RED);
	return (root);
}

/*

*/
rb_tree_t *test_case_2(int **_arr, int *_n)
{
	rb_tree_t *root;
	static int arr[] = {10};

	*_arr = arr;
	*_n = sizeof(arr) / sizeof(int);
	root = rb_tree_node(NULL, 10, BLACK);
	root->left = rb_tree_node(root, 5, BLACK);
	root->right = rb_tree_node(root, 11, BLACK);
	root->right->right = rb_tree_node(root->left, 15, RED);
	return (root);
}

/*
	           .--------------B(040)---.
         .--R(021)---------.        B(043)
   .--B(009)         .--B(033)
R(001)            R(026)
REMOVE 9
*/
rb_tree_t *test_case_3(int **_arr, int *_n)
{
	rb_tree_t *root;
	static int arr[] = {9};

	*_arr = arr;
	*_n = sizeof(arr) / sizeof(int);
	root = rb_tree_node(NULL, 40, BLACK);
	root->left = rb_tree_node(root, 21, RED);
	root->right = rb_tree_node(root, 43, BLACK);
	root->left->left = rb_tree_node(root->left, 9, BLACK);
	root->left->left->left = rb_tree_node(root->left->left, 1, RED);	
	root->left->right = rb_tree_node(root->left, 33, BLACK);
	root->left->right->left = rb_tree_node(root->left->right, 26, RED);
	
	return (root);
}

/*
         .--B(017)---------------.
   .--B(008)         .--------R(028)---.
R(001)            B(021)---.        B(045)
                        R(027)
TRY RM [45]
*/
rb_tree_t *test_case_4(int **_arr, int *_n)
{
	rb_tree_t *root;
	static int arr[] = {45};

	*_arr = arr;
	*_n = sizeof(arr) / sizeof(int);
	root = rb_tree_node(NULL, 17, BLACK);
	root->left = rb_tree_node(root, 8, BLACK);
	root->right = rb_tree_node(root, 28, RED);
	root->left->left = rb_tree_node(root->left, 1, RED);
	root->right->left = rb_tree_node(root->right, 21, BLACK);
	root->right->right = rb_tree_node(root->right, 45, BLACK);
	root->right->left->right = rb_tree_node(root->right->left, 27, RED);
	
	return (root);
}

/*
         .--B(017)---------------.
   .--B(008)         .--------R(028)---.
R(001)            B(021)---.        B(045)
                        R(027)
TRY RM [45]
*/
rb_tree_t *test_case_4b(int **_arr, int *_n)
{
	rb_tree_t *root;
	static int arr[] = {21};

	*_arr = arr;
	*_n = sizeof(arr) / sizeof(int);
	root = rb_tree_node(NULL, 17, BLACK);
	root->left = rb_tree_node(root, 8, BLACK);
	root->right = rb_tree_node(root, 28, RED);
	root->left->left = rb_tree_node(root->left, 1, RED);
	root->right->left = rb_tree_node(root->right, 21, BLACK);
	root->right->right = rb_tree_node(root->right, 45, BLACK);
	root->right->right->right = rb_tree_node(root->right->right, 47, RED);
	
	return (root);
}

rb_tree_t *test_random_array(int len, int max, int *_n, int **array)
{
	rb_tree_t *root = NULL;

	int *arr = rand_array(len, max);
	int n;

	for (n = 0; n < len; n++)
	{
		printf("INSERTING [%d]\n", arr[n]);
		rb_tree_insert(&root, arr[n]);
	}
		
	*_n = len;
	*array = arr;
	return (root);
}

/**
 * is_bst - helper func for binary_tree_is_bst
 * @tree: pointer to tree node
 * @min: minimum value of BST tree
 * @max: maximum value of BST tree
 * Return: true or false
 */
int is_bst(const rb_tree_t *tree, int min, int max)
{
	if (!tree)
		return (1);
	if (tree->n < min || tree->n > max)
		return (0);
	return (is_bst(tree->left, min, tree->n - 1) &&
		is_bst(tree->right, tree->n + 1, max));
}


/**
 * binary_tree_is_bst - checks if a binary tree is a valid Binary Search Tree
 * @tree: pointer to root of tree
 * Return: 1 if true 0 if false
 */
int binary_tree_is_bst(const rb_tree_t *tree)
{
	if (!tree)
		return (0);
	return (is_bst(tree, INT_MIN, INT_MAX));
}

/**
 * rand_array - generates random int array
 *
 * @len: the length of the array
 * @max: the max size of each integer
 * 
 * Return: the generated int array
 */
int *rand_array(int len, int max)
{
	int *arr;

	arr = calloc(len, sizeof(int));
	if (!arr)
		return (NULL);
	if (!max)
		max = RAND_MAX;
	srand(time(NULL));
	while (len--)
		arr[len] = rand() % max;
	return (arr);
}
