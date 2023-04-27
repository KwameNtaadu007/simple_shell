#include "main.h"

/**
 * read_stdin_line - reads a line of input from
 * standard input.
 *
 * @i_eof: return value of getline function
 * Return: input string
 */
char *read_stdin_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
