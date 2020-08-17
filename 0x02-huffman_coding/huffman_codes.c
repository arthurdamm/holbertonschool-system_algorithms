#include "huffman.h"

char *convert(long num, long base);
void print_huffman_codes(binary_tree_node_t *tree, unsigned long path);

/**
 * huffman_codes - generates character codes from huffman tree
 * @data: array of characters
 * @freq: frequency of each character
 * @size: size of data and freq arrays
 * Return: 1 on success else 0
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *tree = huffman_tree(data, freq, size);

	if (!tree)
		return (0);
	print_huffman_codes(tree, 1);
	return (1);
}

/**
 * print_huffman_codes - walks the tree to print the huffman codes
 * @tree: pointer to current tree node
 * @path: long int holding binary representation of path
 */
void print_huffman_codes(binary_tree_node_t *tree, unsigned long path)
{
	symbol_t *symbol;

	if (!tree)
		return;
	symbol = tree->data;
	if (symbol->data != -1)
	{
		printf("%c: %s\n", symbol->data, convert(path, 2) + 1);
	}
	else
	{
		print_huffman_codes(tree->left, path << 1);
		print_huffman_codes(tree->right, (path << 1) + 1);
	}
	free(symbol);
	free(tree);
}
