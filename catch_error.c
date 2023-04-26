#include "main.h"

/**
 * catch_error - trigger error handler based on builtin
 * @crdata: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int catch_error(core_data *crdata, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(crdata);
		break;
	case 126:
		error = error_path_126(crdata);
		break;
	case 127:
		error = error_not_found(crdata);
		break;
	case 2:
		if (_strcmp("exit", crdata->args[0]) == 0)
			error = error_exit_shell(crdata);
		else if (_strcmp("cd", crdata->args[0]) == 0)
			error = error_get_cd(crdata);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	crdata->status = eval;
	return (eval);
}

