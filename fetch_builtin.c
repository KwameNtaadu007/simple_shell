#include "main.h"

/**
 * fetch_builtin - fetches builtin commands that match *cmd
 * @cmd: command
 * Return: function pointer to built-in functions of the shell
 */
int (*fetch_builtin(char *cmd))(core_data *)
{
	builtin_t builtin[] = {
		{"env", _env},
		{"exit", exit_shell},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", ch_dir},
		{"help", give_help},
		{NULL, NULL}};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

