#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define USAGE "./huffman <mode> <filename> <out_filename>\n"

/**
 * main - entry pointer
 * @ac: argument count
 * @av: argument vector
 * Return: SUCCESS OR FAILURE
 */
int main(int ac, char **av)
{
	if (ac != 4)
		return (printf(USAGE), EXIT_FAILURE);
	if (access(av[2], F_OK) == -1)
		return (printf("No such file: %s\n", av[2]), EXIT_FAILURE);
	if (access(av[3], F_OK) != -1)
		return (printf("File already exists: %s\n", av[3]), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
