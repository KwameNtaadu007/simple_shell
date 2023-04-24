#include "main.h"

/**
 * free_data - frees data structure
 *
 * @crdata: data structure
 * Return: no return
 */
void free_data(core_data *crdata)
{
	unsigned int i;

	for (i = 0; crdata->_environ[i]; i++)
	{
		free(crdata->_environ[i]);
	}

	free(crdata->_environ);
	free(crdata->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @crdata: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(core_data *crdata, char **av)
{
	unsigned int i;

	crdata->av = av;
	crdata->input = NULL;
	crdata->args = NULL;
	crdata->status = 0;
	crdata->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	crdata->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		crdata->_environ[i] = _strdup(environ[i]);
	}

	crdata->_environ[i] = NULL;
	crdata->pid = aux_itoa(getpid());
}

/**
 * main - Main Entrance
 *
 * @ac: argument count
 * @av: argument list array
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	core_data crdata;
	(void)ac;

	signal(SIGINT, get_sigint);
	set_data(&crdata, av);
	run_shell(&crdata);
	free_data(&crdata);
	if (crdata.status < 0)
		return (255);
	return (crdata.status);
}

