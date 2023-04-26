#include "main.h"

/**
 * classify_command - finds if command is builtin or otherwise
 *
 * @crdata: data relevant (args)
 * Return: 1 on success.
 */
int classify_command(core_data *crdata)
{
	int (*builtin)(core_data *crdata);

	if (crdata->args[0] == NULL)
		return (1);

	builtin = fetch_builtin(crdata->args[0]);

	if (builtin != NULL)
		return (builtin(crdata));

	return (execute_commands(crdata));
}
