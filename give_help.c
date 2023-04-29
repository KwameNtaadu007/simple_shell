#include "main.h"

/**
 * give_help - function that provides help messages based on builtin
 * @crdata: data structure (args and input)
 * Return: Return 0
 */
int give_help(core_data *crdata)
{

	if (crdata->args[1] == 0)
		sh_help_general();
	else if (_strcmp(crdata->args[1], "setenv") == 0)
		sh_help_setenv();
	else if (_strcmp(crdata->args[1], "env") == 0)
		sh_help_env();
	else if (_strcmp(crdata->args[1], "unsetenv") == 0)
		sh_help_unsetenv();
	else if (_strcmp(crdata->args[1], "help") == 0)
		sh_help();
	else if (_strcmp(crdata->args[1], "exit") == 0)
		sh_help_exit();
	else if (_strcmp(crdata->args[1], "cd") == 0)
		sh_help_cd();
	else if (_strcmp(crdata->args[1], "alias") == 0)
		sh_help_alias();
	else
		write(STDERR_FILENO, crdata->args[0],
				_strlen(crdata->args[0]));

	crdata->status = 0;
	return (1);
}

