#include "main.h"

/**
 * is_valid_integer - checks if a string is a valid positive integer
 *
 * @str: string to check
 * Return: 1 if valid, 0 otherwise
 */
int is_valid_integer(char *str)
{
	if (*str == '\0')
		return (0);

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}

	return (1);
}

/**
 * exit_shell - exits the shell
 *
 * @crdata: relevant data (status and args)
 * Return: 0 on success.
 */
int exit_shell(core_data *crdata)
{
	unsigned long ustatus;
	int is_ustatus, isvalidint;
	char *endptr;

	if (crdata->args[1] != NULL)
	{
		ustatus = strtoul(crdata->args[1], &endptr, 10);
		is_ustatus = ustatus > INT_MAX;
		isvalidint = !is_valid_integer(crdata->args[1]);

		if (*endptr != '\0' || isvalidint || is_ustatus)
		{
			catch_error(crdata, 2);
			crdata->status = 2;
			return (1);
		}
		crdata->status = (int)(ustatus % 256);
	}

	return (0);
}

