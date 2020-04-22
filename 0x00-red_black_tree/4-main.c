#include <stdlib.h>
#include "rb_trees.h"
#include <limits.h>
#include <time.h>

rb_tree_t *test_case_0(int **_arr, int *_n);
rb_tree_t *test_case_1(int **_arr, int *_n);
rb_tree_t *test_case_2(int **_arr, int *_n);
rb_tree_t *test_case_3(int **_arr, int *_n);
rb_tree_t *test_case_4(int **_arr, int *_n);
rb_tree_t *test_case_4b(int **_arr, int *_n);
rb_tree_t *test_case_5(int **_arr, int *_n);
rb_tree_t *test_case_random(int **_arr, int *_n);
int test_tree(rb_tree_t *tree, int *arr, int n);
int binary_tree_is_bst(const rb_tree_t *tree);
int *rand_array(int len, int max);
rb_tree_t *test_random_array(int len, int max, int *_n, int **array);
int tree_contains(rb_tree_t *tree, int n);

#define VERBOSE 0
#define _RAND_LEN 50
#define _RAND_MAX 100

/**
 * main - Entry point
 *
 * Return: 0 on success, error code on failure
 */
int main(void)
{
	rb_tree_t *tree;

	rb_tree_t *(*test_funcs[])(int **, int *) = {
		test_case_0,
		test_case_1,
		test_case_2,
		test_case_3,
		test_case_4,
		test_case_4b,
		test_case_5,
		test_case_random,
		NULL
	};
	int *arr;
	int n, i;
	
	for (i = 0; test_funcs[i]; i++)
	{
		tree = test_funcs[i](&arr, &n);
		if (!test_tree(tree, arr, n))
			printf(ARED "TEST [%d] FAILED!\n" RES, i);
		else
			printf(GRN "TEST [%d] OK.\n" RES, i);
		
	}
	return (0);
}


int test_tree(rb_tree_t *tree, int *arr, int n)
{
	if (!tree)
		return (1);
	if (n < 20 && VERBOSE)
		rb_tree_print(tree);
	if (!rb_tree_is_valid(tree))
	{
		printf(ARED "Error RECEIVED tree invalid RB!\n" RES);
		return (0);
	}
	else if (!binary_tree_is_bst(tree))
	{
		printf(ARED "Error RECEIVED tree invalid BST!\n" RES);
		return (0);
	}
	else if (VERBOSE)
	{
		printf(GRN "\nVALID TREE\n\n" RES);
	}
	fflush(stdout);
	for (n--; n >= 0; n--)
	{
		int t = arr[n], removed = 0;
		if (tree_contains(tree, t))
			removed = 1;
		tree = rb_tree_remove(tree, t);
		if (n < 20 && VERBOSE && removed)
			rb_tree_print(tree);
		if (VERBOSE && removed)
			printf(YEL "REMOVED [%d]\n" RES, t);
		if (tree == NULL)
			return (1);
		if (!rb_tree_is_valid(tree))
		{
			printf(ARED "Error tree invalid RB!\n" RES);
			return (0);
		}
		else if (!binary_tree_is_bst(tree))
		{
			printf(ARED "Error tree invalid BST!\n" RES);
			return (0);
		}
	}
	return (1);
}

rb_tree_t *test_case_0(int **_arr, int *_n)
{
	int input[] = {
		79, 47, 68, 87, 84, 91, 21, 32, 34, 2,
		20, 22
	};
	int n = sizeof(input) / sizeof(input[0]);
	static int arr[] = { 22, 20, 2, 34, 32 };

	*_arr = arr;
	*_n = sizeof(arr) / sizeof(int);
	return (array_to_rb_tree(input, n));
}

rb_tree_t *test_case_1(int **_arr, int *_n)
{
	rb_tree_t *root;
	static int arr[] = {10};

	*_arr = arr;
	*_n = sizeof(arr) / sizeof(int);
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

rb_tree_t *test_case_5(int **_arr, int *_n)
{
	int input[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	int n = sizeof(input) / sizeof(input[0]);
	static int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

	*_arr = arr;
	*_n = sizeof(arr) / sizeof(int);
	return (array_to_rb_tree(input, n));
}

rb_tree_t *test_case_random(int **_arr, int *_n)
{
	return (test_random_array(_RAND_LEN, _RAND_MAX, _n, _arr));
}

rb_tree_t *test_random_array(int len, int max, int *_n, int **array)
{
	rb_tree_t *root = NULL;

	int *arr = rand_array(len, max);
	int n;

	for (n = 0; n < len; n++)
	{
		/* printf("INSERTING [%d]\n", arr[n]); */
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

int tree_contains(rb_tree_t *tree, int n)
{
	while (tree)
	{
		if (n > tree->n)
			tree = tree->right;
		else if (n < tree->n)
			tree = tree->left;
		else
			return (1);
	}
	return (0);
}
