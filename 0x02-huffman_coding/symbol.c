#include "huffman.h"

/**
 * symbol_create - allocates a new symbol_t struct
 * @data: data field for struct
 * @freq: freq field for struct
 * Return: new symbol_t struct or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = calloc(1, sizeof(*symbol));

	if (!symbol)
		return (NULL);
	symbol->data = data;
	symbol->freq = freq;
	return (symbol);
}
