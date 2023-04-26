#include "main.h"

/**
 * trim_comment - trim comments off of inputs
 *
 * @str_in: input string
 * Return: input without comments
 */
char *trim_comment(char *str_in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; str_in[i]; i++)
	{
		if (str_in[i] == '#')
		{
			if (i == 0)
			{
				free(str_in);
				return (NULL);
			}

			if (str_in[i - 1] == ' ' || str_in[i - 1] == '\t' || str_in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		str_in = _realloc(str_in, i, up_to + 1);
		str_in[up_to] = '\0';
	}

	return (str_in);
}

/**
 * run_shell - running of shell
 * @crdata: data relevant (av, input, args)
 *
 * Return: no return.
 */
void run_shell(core_data *crdata)
{
	char *input;
	int i_eof;
	int running = 1;

	while (running == 1)
	{
		write(STDIN_FILENO, ":)$ ", 5);
		input = read_stdin_line(&i_eof);
		if (i_eof == -1)
		{
			free(input);
			running = 0;
		}
		else
		{
			input = trim_comment(input);
			if (input == NULL)
				continue;

			if (if_syntax_error(crdata, input) == 1)
			{
				crdata->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, crdata);
			running = split_commands(crdata, input);
			crdata->counter += 1;
			free(input);
		}
	}
}
